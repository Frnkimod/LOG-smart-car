import sys
import os
from prompt_toolkit import PromptSession
from prompt_toolkit.completion import WordCompleter
from prompt_toolkit.key_binding import KeyBindings
from prompt_toolkit.styles import Style
from prompt_toolkit.formatted_text import FormattedText
from prompt_toolkit.shortcuts import print_formatted_text
import argparse
import json
import datetime
from pyfiglet import Figlet
from termcolor import colored

str_loge="""\r███████╗██████╗  █████╗ ███╗   ██╗██╗  ██╗██╗\r
            \r██╔════╝██╔══██╗██╔══██╗████╗  ██║██║ ██╔╝██║\r
            \r█████╗  ██████╔╝███████║██╔██╗ ██║█████╔╝ ██║\r
            \r██╔══╝  ██╔══██╗██╔══██║██║╚██╗██║██╔═██╗ ██║\r
            \r██║     ██║  ██║██║  ██║██║ ╚████║██║  ██╗██║\r
            \r╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝\r"""
def read_info_json():
    with open('info.json','r') as json_file:
        buf_info=json.load(json_file)
    return buf_info
def write_info_json(author):

    data_buf=read_info_json()
    data_buf['author']=author
    with open('info.json','w') as jsos_file:
        json.dump(data_buf,jsos_file,indent=4)
def create_c_code(file,author):
    return f"""// {file}.c
// Author: {author}
// Date: {datetime.date.today().strftime("%Y-%m-%d")}
#include "{file}.h"

// Your C functions and implementation go here"""

def create_h_code(file,author):
    header_guard = file.upper() + "_H"
    return f"""// {file}.h
// Author: {author}
// Date: {datetime.date.today().strftime("%Y-%m-%d")}

#ifndef {header_guard}
#define {header_guard}

// Your function prototypes and declarations go here

#endif // {header_guard}"""

def clear_screen():
    # 对于 Windows
    if os.name == 'nt':
        os.system('cls')
    # 对于 Unix/Linux/MacOS
    else:
        os.system('clear')
from alive_progress import alive_bar
from selenium.webdriver.common.devtools.v85.log import clear

bindings = KeyBindings()
@bindings.add('c-c')
def _(event):
    " Exit when `ctrl-c` is pressed. "
    event.app.exit()

def auto_author(session):
    info= read_info_json()
    author_name=info['author']
    out_file=info['out_file']
    module_name=session.prompt('输入模块名称>>> ') #input("输入模块名称:")
    file_name=session.prompt('输入创建.c/.h名称>>> ')    #input("输入创建.c/.h名称:")
    if not os.path.exists(f"{out_file}/{module_name}"):
         # 文件夹不存在，创建文件夹
         os.makedirs(f"{out_file}/{module_name}")
    # 写入C文件
    with open(f"{out_file}/{module_name}/{file_name}.c", "w") as c_file:
        c_file.write(create_c_code(file_name,author_name))
    # 写入头文件
    with open(f"{out_file}/{module_name}/{file_name}.h", "w") as h_file:
        h_file.write(create_h_code(file_name,author_name))

def set_author(session):
    author_name=session.prompt('输入你的名称>>> ') #input('输入你的名称')
    write_info_json(author_name)
    auto_author(session)

def exit(session):
    clear_screen()
    sys.exit()


pages={
    'A1生成C模块(默认模式)':{
        'A1设置作者信息':set_author,
        'A2默认作者':auto_author,
        'A3退出':exit,
    },
    'A2生成C模块(高级模式)':{
        'A1设置作者信息':set_author,
        'A2默认作者':auto_author,
        'A3退出':exit,
    },
    'A3退出':exit
}
def navigate(session, pages):
    try:
        while True:
            if isinstance(pages, dict):
                clear_screen()
                print(str_loge)
                for v in pages:
                    print_formatted_text(FormattedText([
                        ('class:output', f'{v}'),
                    ]), style=session.style)

                choice = session.prompt('请选择（输入选项编号或 "back" 返回上一级)>>>', completer=WordCompleter(pages))

                if choice == 'back':
                    return
                elif choice in pages:
                    if isinstance(pages[choice], dict):
                        navigate(session, pages[choice])
                    else:
                        pages[choice](session)
                else:
                    session.message = '无效的选择，请重新输入。'
            else:
                pages(session)
                break
    except KeyboardInterrupt:
        print_formatted_text(FormattedText([
            ('class:prompt', 'Ctrl+c程序退出'),
        ]), style=session.style)



def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-a',help='作者名称')
    parser.add_argument('-m',help='模块名称')
    parser.add_argument('-o',help='输出路径')
    parser.add_argument('-f',help='c/h文件名称')

    args= parser.parse_args()
    if args.a and args.m and args.o and args.f:
        author_name=args.a
        out_file=args.o
        module_name=args.m
        file_name=args.f
        if not os.path.exists(f"{out_file}/{module_name}"):
            # 文件夹不存在，创建文件夹
            os.makedirs(f"{out_file}/{module_name}")
        # 写入C文件
        with open(f"{out_file}/{module_name}/{file_name}.c", "w") as c_file:
            c_file.write(create_c_code(file_name,author_name))
        # 写入头文件
        with open(f"{out_file}/{module_name}/{file_name}.h", "w") as h_file:
            h_file.write(create_h_code(file_name,author_name))
        return
    else:
        # 定义自定义样式
        custom_style = Style.from_dict({
            'prompt': '#ff0066 bold',
            'loge':'#00FFFF',
            'input': '#0000ff',
            'output': '#00ff00',
        })
        session = PromptSession(style=custom_style)
        navigate(session, pages)
if __name__ == "__main__":
    main()
    sys.exit()
