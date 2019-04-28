from socketserver import *
import os, json, struct,pprint
import threading
import pexpect

test_home = "0.0.0.0"
PORT = 8875
TEST_HOME = (test_home, PORT)
base_dir = os.path.dirname((os.path.abspath(__file__)))
DISPLAY = []
PARAMS = []
flag = 0
allowToReceiveArgs=False


def compile(cmd):
    os.system(cmd)


# 将用户的输入从列表取出传给控制台
def sendto_console(child):
    global PARAMS
    alreadySendFlag=False
    while True:
        if len(PARAMS)>0:
            print("already get the args")
            child.sendline(PARAMS.pop(0).encode('utf-8'))
            break
        else:
            if not alreadySendFlag:
                global allowToReceiveArgs
                allowToReceiveArgs=True                            # 开始接收参数
                alreadySendFlag=True
            continue


# 将控制台的输出保存到列表发给用户
def sendto_client(content):
    DISPLAY.append(str(content,encoding='utf-8'))


# 调动解析器执行客户端的文件
def interact(cmd):
    global PARAMS
    PARAMS=[]
    print("running cmd: "+cmd)
    child = pexpect.spawn(cmd)
    child.setecho(False)
    child.timeout = 0.5
    while True:
        print("try to run")
        try:
            child.expect('.+')
            if not child.isalive():
                print("run cmd to the end")
                print(child.after.strip())
                sendto_client(child.after.strip())                # 回送结果
                global flag
                flag = 1                                        # 结束标志
                break
            sendto_client(child.after)
            sendto_console(child)
        except:
            print("some exception happen while runnnig the cmd")
            sendto_console(child)


# 主函数，根据文件类型调用相应解析器执行
def call(filename, filetype):
    if filetype == 'C':
        compile_c(filename)
    elif filetype == 'C++':
        compile_c_plus(filename)
    elif filetype == 'Java':
        compile_java(filename)
    elif filetype == 'python':
        compile_python(filename)
    elif filetype == 'python3':
        compile_python3(filename)


def compile_python(filename):
    cmd = 'python ' + filename
    interact(cmd)


def compile_python3(filename):
    cmd = 'python3 ' + filename
    interact(cmd)


def compile_c(filename):
    os.system("rm -f app")
    cmd = 'gcc ' + filename + ' -o app -lm'
    os.system(cmd)
    cmd = 'bash -c "./app"'
    interact(cmd)


def compile_c_plus(filename):
    os.system("rm -f app")
    cmd = 'g++ ' + filename + ' -o app'
    os.system(cmd)
    cmd = 'bash -c "./app"'
    interact(cmd)


def compile_java(filename):
    cmd = 'javac ' + filename
    os.system(cmd)
    os.system("rm -f "+filename)
    file = filename[:-5]
    print(file)
    cmd = 'bash -c "java '+file+'"'
    interact(cmd)


class MyRequestHandler(StreamRequestHandler):
    def feedback(self):  # send to client
        while True:
            if not DISPLAY:    #没有数据等待发送
                continue
            self.request.send(DISPLAY.pop(0).encode('utf-8'))
            global flag
            if flag==1:
                break
                
    def paramReceive(self):                                          # 获得来自客户端的参数信息，将将其作为字符串发给CMD
        while True:
            try:
                global flag
                if flag==1:                                            # 判断程序是否结束
                    break
            
                global allowToReceiveArgs
                if not allowToReceiveArgs:                            # 只在需要输入的时候读取输入
                    continue
                
                print('wait to receive args from client')
                param = self.request.recv(1024).decode('utf-8')       #接收参数
                
                if not param:
                    continue

                allowToReceiveArgs=False
                print('success to receive args from client')
                
                #pprint.pprint(param)
                PARAMS.append(param)
                #pprint.pprint(PARAMS)
            except:
                print('some exception happen while waiting to receive args from client')
                break


    def upload(self, hander):  # 客户端上传文件，服务器接收
        try:
            filesize = hander['filesize']
            whole_data = b''
            current_size = 0
            while current_size < filesize:
                data = self.request.recv(1024)
                current_size = current_size + len(data)
                whole_data = whole_data + data
                filename = hander['filename']
                i = 0
            #print(whole_data)
            while True:
                if os.path.exists(filename):  # 该文件存在则不停在后缀前+1直至不存在
                    filename_list = filename.rsplit(".", maxsplit=1)
                    filename = filename_list[0] + str(i) + "." + filename_list[1]
                    i = i + 1
                else:
                    f = open(filename, "w", encoding="utf-8")
                    f.write(str(whole_data,encoding='utf-8'))
                    f.close()
                    return filename
        except:
            return ""


    def handle(self):# 定义处理方法  一开始等待对方发送数据包，
        try:
            while True:
                global flag
                global PARAMS
                global allowToReceiveArgs
                allowToReceiveArgs=False
                flag = 0
                PARAMS = []
                json_length = self.request.recv(4)                                      # 对方发送的json_hander数据包长度，为int型变量，为json型，其中包含flag和文件名称，文件大小
                
                json_hander=b''
                while len(json_hander)<struct.unpack('i', json_length)[0]:
                    info = self.request.recv(struct.unpack('i', json_length)[0])      # 收到json型的hander json_hander的是结构化的json_hander，它的[0]是json_hander的长度
                    json_hander+=info
                    
                hander = json.loads(json_hander.decode("utf-8"))
                order = hander['order']
                # hander = {'order': 'upload', 'filename': 'notepad.cpp', 'filesize': 60, "language": "C"}(例如)
                if order == 'upload':
                    result = self.upload(hander)
                    if not result:
                        print("fail to get the source file name")
                        return False
                        
                    t1 = threading.Thread(target=self.feedback)                            # 回送消息线程
                    t2 = threading.Thread(target=self.paramReceive)                        # 接收消息线程
                    t1.start()
                    t2.start()
                    
                    call(result, hander['language'])
                    os.system("rm -f "+result)
                    t1.join()
                    print("program come to the end.")
                    self.request.shutdown()
        except:
            return 0


if __name__ == '__main__':
    server = ThreadingTCPServer(TEST_HOME, MyRequestHandler)
    server.serve_forever()
