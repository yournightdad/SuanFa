# ### 文法类隐写与分析技术的实现
# 
# * 1、完成位图格式图像的头文件冗余的数据隐写、分析和提取。
# 
# * 2、完成文件尾部追加的数据隐写、分析和提取： 
#    
# 
# * 3、完成BMP位图格式图像的数据区进行数据直接覆盖方式的隐写和分析。
#

# In[2]:


#导入所需要的库
import os, sys
import struct
import shutil
from Pillow import Image




# In[2]:


#设定图片以及隐藏信息的路径（路径自己设定越简单和短越好，推荐路径尽可能为英文路径，减少汉字路径的使用，orignal_path表示原图的路径，其余的copy_path是各种隐写后的图片路径，max和min表示隐写的文件，一个隐写内容多，一个隐写内容少，但是全是英文字母，切记不要是中文）
orignal_path ="D:/作业用图/12_1.bmp"
copy_path1 = "D:/隐写后图片/steg_12_1_head.bmp"
copy_path2 = "D:/隐写后图片/steg_12_1_eof.bmp"
copy_path3 = "D:/隐写后图片/steg_12_1_data.bmp"
fsize = os.path.getsize(orignal_path)
fmax = open('D:/隐写信息/max.txt', 'r')
datamax = fmax.read()
fmin = open('D:/隐写信息/min.txt', 'r')
datamin = fmin.read()


# In[4]:


# 读取BMP文件数据判断
#Bmp位图文件是基于16进制的，我们需要以16进制的方式去读取文件，
#在python中有一个官方模块struct，里面内置了pack和unpack两个函数，我们可以使用这两个函数对16进制的信息进行打包和解包
def bmp_info(f):
    unpackbuf = struct.unpack('<ccIIIIIIHH', f)  # unpack函数对于16进制信息进行解包
    #’ccIIIIIIHH‘---→格式符 当打包或者解包的时,需要按照特定的方式来打包或者解包.该方式就是格式化字符串
    if (unpackbuf[0] != b'B' or unpackbuf[1] != b'M'):  # 前两个字节是“BM”，用于识别BMP文件的标志
        return None
    else:
        return {
            'bfSize': unpackbuf[2],#4字节整数：表示位图大小
            'bfRserverd': unpackbuf[3],#4字节整数：保留位，始终为0
            'bfOffBits': unpackbuf[4],#4字节整数：实际图像的偏移量
            'biSize': unpackbuf[5],#4字节整数：Header所需的字节数
            'biWidth': unpackbuf[6],#4字节整数：图像宽度
            'biHeight': unpackbuf[7], #4字节整数：图像高度
            'biPlames':unpackbuf[8],# #一个2字节整数：颜色平面数，始终为1
            'biBitCount': unpackbuf[9]#一个2字节整数：比特数/像素。
        }





# 头文件冗余隐写：修改文件头中的保留字段隐藏信息
def header_stegano():
    shutil.copy(orignal_path, copy_path1)#复制文件从src到dst。
    with open(copy_path1, 'r+b') as sfr: #已读写二进制模式打开文件
        str = input('请输入需要隐写的信息:  ')
        sfr.seek(0x0006)#用于移动文件读取指针到指定位置。地址偏移，即保留位的四字节
        sfr.write(str.encode())# 以 encoding 指定的编码格式编码字符串
        sfr.close()
        print("信息隐写成功，请查看隐写后图片的文件夹")
    Operation()


# In[6]:


# 头文件分析
def header_analysis():
    with open(copy_path1, 'rb') as afr:
        afr.seek(0x0006)
        ReserverData = afr.read(4)#读取4字节的数据
        if (ReserverData != 0x0000):
            print("信息隐写成功")
            print("头文件隐写的信息是: ",ReserverData.decode())
        f = open('D:/隐写信息/hidden_header.txt', mode='w')  # 打开文件，若文件不存在系统自动创建。
        f.write(ReserverData.decode())#以 encoding 指定的编码格式解码字符串
        f.close()
    Operation()


# In[7]:


#尾部追加隐写
def eof_stegano():
    shutil.copy(orignal_path, copy_path2)
    with open(copy_path2, 'r+b') as sfr:
        sfr.seek(0, 2)
        print("1.数据量较大（>25%） 2.数据量较小（<1%） ")
        flag = eval(input("请选择: "))#执行选择的命令,并返回表达式的值
        print("")
        if flag == 1:
            sfr.write(datamax.encode())#写入 max的文件内容
            sfr.close()
            print("隐写成功，请查看隐写后图片的文件夹")
            Operation()
        elif flag == 2:
            sfr.write(datamin.encode())#写入 min 文件内容
            sfr.close()
            print("隐写成功，请查看隐写后图片的文件夹")
            Operation()
        else:
            print("Error! Please input again: ")
            Steganography()


# In[8]:


#尾部分析
def eof_analysis():
    with open(copy_path2, 'rb') as afr:
        im = Image.open(copy_path2)  # 返回一个Image对象
        print("------------------------------")
        print('bfwidth：%d, bfheight：%d ' % (im.size[0], im.size[1]))
        size = len(afr.read())
        print("图片实际大小为 {} byte".format(size))
        print("------------------------------")
        flag = eval(input("please input 位深度:"))#24位位图 和 8位位图选项
        # 24位图，一个像素点占3个字节 14位文件头，40位信息头，无调色板
        if flag == 24:
            orignalBytesphoto = im.size[0] * im.size[1] * 3 + 14 + 40
        # 8位位图，一个像素点占1个字节 14位文件头，40位信息头，有颜色表，每个颜色表结构体是4字节，无调色板
        elif flag == 8:
            orignalBytesphoto = im.size[0] * im.size[1] + 14 + 40 + 256 * 4
        else:
            print("Error! Please input again: ")
        afr.seek(fsize)
        ReserverData = afr.read(size - orignalBytesphoto)#保留信息，通过判断源文件和隐写后的图片大小对比
        if (ReserverData != 0x0000):#差不为0 则隐写过
            print("信息隐写成功")  # 判断是否被隐写
            print("The data hidden in the end file is in message 文件夹")
            f = open('D:/隐写信息/hidden_end.txt', mode='w')  # 打开文件，若文件不存在系统自动创建。
            f.write(ReserverData.decode())
            f.close()
        else:
            print("该图片没有被隐写!")
        Operation()


# In[9]:

#数据区的直接覆盖隐写
def bmp_data():
    shutil.copy(orignal_path, copy_path3) #文件复制
    with open(copy_path3, 'r+b') as sfr:
        sfr.seek(0x0054)     #到指定的位置
        print("1.数据量较大（>25%） 2.数据量较小（<1%） ")
        flag = eval(input("请选择: "))
        print("")
        if flag == 1:
            sfr.write(datamax.encode())#写入 datamax内容
            sfr.close()
            print("隐写成功，请查看隐写后图片的文件夹")
            Operation()
        elif flag == 2:
            sfr.write(datamin.encode()) #写入 datamin内容
            sfr.close()
            print("隐写成功，请查看隐写后图片的文件夹")
            Operation()
        else:
            print("Error! Please input again: ")
            Steganography()


# In[1]:

#数据分析  指针移动到偏移位置读取字节的信息长度
def bmp_data_analysis():
    with open(copy_path3, 'rb') as afr:
        afr.seek(0x0054)    #移动到指定位置
        ReserverData = afr.read(len(datamax))  #max文件内容
        if (ReserverData != 0x0000):
            print("信息隐写成功")
            print("The data hidden in te bmp_data file is in message 文件夹")
            f = open('D:/隐写信息/hidden_data.txt', mode='w')  # 打开文件，若文件不存在系统自动创建。
            f.write(ReserverData.decode())  #写入内容到 hidden_data 文件中
            f.close()
            Operation()


# In[11]:


def Steganography():
    print("*********************************")
    print("1.头文件冗余部分的隐写")
    print("2.文件尾部追加隐写")
    print("3.数据区直接覆盖的隐写")
    print("4.退出")
    print("*********************************")
    flag = eval(input("Please input your choice: "))
    print("")
    if flag == 1:
        header_stegano()
    elif flag == 2:
        eof_stegano()
    elif flag == 3:
        bmp_data()
    elif flag == 4:
        Operation()
    else:
        print("Error! Please input again: ")
        Steganography()


# In[12]:


def Analysis():
    print("*********************************")
    print("1.头文件冗余部分的分析")
    print("2.文件尾部追加分析")
    print("3.数据区直接覆盖的分析")
    print("4.退出")
    print("*********************************")
    flag = eval(input("Please input your choice: "))
    print("")
    if flag == 1:
        header_analysis()
    elif flag == 2:
        eof_analysis()
    elif flag == 3:
        bmp_data_analysis()
    elif flag == 4:
        Operation()
    else:
        print("Error! Please input again: ")
        Analysis()


#[13]:


def Operation():
    print("*********************************")
    print("1.隐写")
    print("2.分析")
    print("3.退出")
    print("*********************************")
    flag = eval(input("Please input your choice: "))
    print("")
    if flag == 1:
        Steganography()
    elif flag == 2:
        Analysis()
    elif flag == 3:
        sys.exit()
    else:
        print("Error! Please input again: ")
        Operation()





if __name__ == '__main__':
    Operation()
