# coding: utf-8


from wsgiref.simple_server import make_server


def application(environ, start_response):
    print(environ, start_response)
    start_response('200 OK', [('Content-Type', 'text/html')])
    return [b'<h1> Hello,</h1>']

httpd = make_server('', 8003, application)
print ('start')
httpd.serve_forever()