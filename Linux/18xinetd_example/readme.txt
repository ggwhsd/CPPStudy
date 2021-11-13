利用xinetd网络守护进程去调用一些负载较小的网络服务中需要用到的程序。
利用配置xientd对应的端口和调用自定义程序。

1. ls /etc/xinetd.conf 查看配置文件，这个文件一般不用修改，里面设置了包含目录xinetd.d
2. cd /etc/xinetd.d
3. 编写自定义程序 daytime_inetd 输出当前系统时间
4. 将其拷贝到/root/daytime_inetd
5. 在xinetd.d下，执行vi daytime_inetd，输入如下内容
   service daytime_inetd
   {
      disable = no
	  flags = REUSE
	  socket_type = stream
	  wait = no
	  user = root
	  server = /root/daytime_netd
	  log_on_failure += USERID
   }
6. 在/etc/services中指定端口，这样xinetd知道利用哪个端口来和daytime_inetd进行绑定处理。
   daytime_inetd 8888/tcp

7. 重启网络xinetd服务
   service xinetd restart

8. 测试,telnet localhost 8888, 如果会出现日期时间，则测试成功。






