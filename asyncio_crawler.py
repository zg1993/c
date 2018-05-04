# coding: utf8

import socket
# import Queue
import time
import traceback

from selectors import DefaultSelector, EVENT_WRITE, EVENT_READ

# print (type(DefaultSelector))

# q = Queue.Queue()


def fetch_block(url):
    sock = socket.socket()
    sock.connect(('xkcd.com', 80))
    request = 'GET {0} HTTPS/1.0\r\nHOST: xkcd.com\r\n\r\n'.format(url)
    sock.send(request.encode('ascii'))
    response = b''
    chunk = sock.recv(4096)
    while chunk:
        response += chunk
        chunk = sock.recv(4096)
    print (response)
    # print type(chunk)
    # print chunk



def fetch_unblock(url):
    sock = socket.socket()
    sock.setblocking(False)
    # print time.time()
    try:
        sock.connect(('xkcd.com', 80))
    # except BlockingIOError:
    #     print traceback.format_exc()
    except Exception as e:
        pass
        # print (e)
        # print 1
        # print traceback.format_exc()
    # print time.time()
    request = 'GET {0} HTTP/1.0\r\nHOST: xkcd.com\r\n\r\n'.format(url)
    encoded = request.encode('ascii')
    while True:
        try:
            sock.send(encoded)
            break
        # except OSError:
        #     print 2
        #     print traceback.format_exc()
        except Exception as e:
            pass
            # print (e)
            # print 2
            # print e
    print ('sent')
    # sock.send(request.encode('ascii'))
    response = b''
    while True:
        try:
            chunk = sock.recv(4096)

            # print 'receive success'
            break
        except Exception as e:
            pass
            # print (e, 3)
            # print 3
            # print e
            # print traceback.format_exc()
    print (chunk)


selector = DefaultSelector()
stopped = False


def loop():
    # while True:
    while not stopped:
        print ('block select')
        events = selector.select() # 阻塞直到register的描述符事件准备好
        for event_key, event_mask in events:
            callback = event_key.data
            print (callback, event_mask, event_key.fd)
            callback(event_key, event_mask)


def fetch_selector(url):
    sock = socket.socket()
    sock.setblocking(False)
    try:
        sock.connect(('xkcd.com', 80))
    except Exception as e:
        print(e)

    def connected():
        # dir(selector)
        selector.unregister(sock.fileno())
        print('connected', sock.fileno())

    selector.register(sock.fileno(), EVENT_WRITE, connected)


class Future:
    def __init__(self):
        self.result = None
        self._callbacks = []

    def add_done_callback(self, fn):
        self._callbacks.append(fn)

    def set_result(self, result):
        self.result = result
        for fn in self._callbacks:
            fn(self)


class Task:
    def __init__(self, coro):
        self.coro = coro
        f = Future()
        print (f)
        f.set_result(None)
        self.step(f)

    def step(self, future):
        print ('step future', future)
        try:
            next_future = self.coro.send(future.result)
            print ('next_future', next_future)
        except StopIteration:
            print('generator end')
            return
        next_future.add_done_callback(self.step)


class Fetcher:
    def __init__(self, url):
        self.response = b''
        self.url = url
        self.sock = None

    # generator version
    def fetch(self):
        print ('fetch start')
        self.sock = socket.socket()
        self.sock.setblocking(False)
        try:
            self.sock.connect(('xkcd.com', 80))
        except Exception as e:
            pass
        f = Future()
        print('send before', f)

        def on_connected(key, mask):
            print ('connect')
            f.set_result('hello') # test send

        selector.register(self.sock.fileno(), EVENT_WRITE, on_connected)
        print ('fetch start 1')
        r = yield f
        print ('send after', f)
        print ('send after r ', r)
        selector.unregister(self.sock.fileno())
        request = 'GET {0} HTTP/1.0\r\nHOST: xkcd.com\r\n\r\n'.format(self.url)
        encoded = request.encode('ascii')
        self.sock.send(encoded)

        # yield from
        self.response = yield from self.read_all()

        # while True:
        #     f = Future()
        #     sock = self.sock
        #
        #     def on_readable(key, mask):
        #         print ('ready read')
        #         f.set_result(sock.recv(4096))
        #     selector.register(self.sock.fileno(),
        #                       EVENT_READ,
        #                       on_readable)
        #     chunk = yield f
        #     selector.unregister(self.sock.fileno())
        #     if chunk:
        #         self.response += chunk
        #     else:
        #         print ('done reading', self.response)
        #         # Done reading
        #         break
        print (self.response)

    def read(self):
        f = Future()
        sock = self.sock
        def on_readable(key, mask):
            f.set_result(sock.recv(4096))
        selector.register(sock.fileno(), EVENT_READ, on_readable)
        chunk = yield f
        selector.unregister(sock.fileno())
        return chunk

    def read_all(self):
        response = []
        chunk = yield from self.read()
        while chunk:
            response.append(chunk)
            chunk = yield from self.read()
        return b''.join(response)


    # def fetch(self):
    #     self.sock = socket.socket()
    #     self.sock.setblocking(False)
    #     try:
    #         self.sock.connect(('xkcd.com', 80))
    #     except Exception as e:
    #         pass
    #     selector.register(self.sock.fileno(), EVENT_WRITE, self.connected)


    def connected(self, key, mask):
        print ('connected')
        selector.unregister(key.fd)
        request = 'GET {0} HTTP/1.0\r\nHOST: xkcd.com\r\n\r\n'.format(self.url)
        encoded = request.encode('ascii')
        self.sock.send(encoded)
        selector.register(key.fd, EVENT_READ, self.read_response)

    def read_response(self, key, mask):
        print ('read_response')
        global stopped
        chunk = self.sock.recv(4096)
        print ('chunk', chunk)
        if chunk:
            self.response += chunk
        else:
            selector.unregister(key.fd)
            print (self.response)
            print (len(self.response))


if __name__ == '__main__':
    fetcher = Fetcher('/353/')
    gen = fetcher.fetch()
    Task(gen)
    # print (type(gen))
    loop()
    # fetch_selector('/')
    # loop()
    # fetch_block('/353/')