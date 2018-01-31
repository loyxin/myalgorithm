#!/usr/bin/python
# coding=utf8

# -*- coding: utf-8 -*-
# use:
# python3 sysulib.py -m http.server
# 需要安装的库: requests
# 其实就是图书馆网站的一个bug
# http://blog.csdn.net/sinat_37841010/article/details/62041927?locationNum=7&fps=1
import requests
import json
from urllib.parse import parse_qs
from http.server import HTTPServer, BaseHTTPRequestHandler

form = '''<!DOCTYPE html>
  <title>Message Board</title>
  <form method="POST">
    <text>学号</text>
    <textarea name="cardNo"></textarea>
    <br>
    <button type="submit">Post it!</button>
  </form>
  <pre>
{}
  </pre>
'''

memory = []


def update_record_status(self, login_html):
    login_json = json.loads (login_html.text)
    if login_json['resultNum']:
        self.send_response (200)
        self.send_header ('Content-type', 'text/plain; charset=utf-8')
        self.end_headers ()
        self.wfile.write ("您没有过期记录，不需要做题".encode ())
    else:
        recordId = str (login_json['record']['id'])
        update_url = 'http://202.116.65.85/library/UpdateRecordStatus.action?recordId=' + recordId

        update_data = {'recordId': recordId}

        update_html = requests.get (update_url, cookies=login_html.cookies, data=update_data,
                                    headers=login_html.headers)

        update_json = json.loads (update_html.text)
        self.send_response (200)
        self.send_header ('Content-type', 'text/plain; charset=utf-8')
        self.end_headers ()
        self.wfile.write ("名字'{}'做题完成！".format (update_json['record']['name']).encode ())

def login_library(cardNo):

    login_url = 'http://202.116.65.85/library/CheckOverdueRecord.action'
    login_data = {'cardNo': cardNo}
    login_headers = {
                'Host': '202.116.65.85',
                'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64; rv:49.0) Gecko/20100101 Firefox/49.0',
                'Referer': 'http://202.116.65.85/sysulib/',
                'Connection': 'keep-alive'
    }

    login_html = requests.post(login_url, data=login_data, headers=login_headers)

    return login_html

class MessageHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        self.send_response(200)

        self.send_header('Content-type', 'text/html; charset=utf-8')
        self.end_headers()

        # Send the form with the messages in it.
        mesg = form.format("\n".join(memory))
        self.wfile.write(mesg.encode())

    def do_POST(self):
        length = int(self.headers.get('Content-length', 0))

        # Read and parse the message
        data = self.rfile.read(length).decode()
        cardNo = parse_qs(data)["cardNo"][0]
        login_html = login_library(cardNo)
        update_record_status(self,login_html)





if __name__ == '__main__':
    server_address = ('', 8000)
    httpd = HTTPServer(server_address, MessageHandler)
    httpd.serve_forever()
