# 登录服务器的图形界面

## 本地

- 设定sshd：在`/etc/ssh/sshd_config`中，打开X11Forward。


- 在本地终端，
```bash
export DISPLAY=:0.0 # 因为它是用来生成新的 X11 授权信息的。生成的授权信息会在本地添加到授权列表中，并随后通过 SSH 连接传输到远程服务器。

xauth list $DISPLAY # 这将显示当前 X11 显示的授权信息
xauth add <显示的授权信息> # 将该信息添加到新的授权列表中

ssh -Y hostname@ip
```


## 远程 
```bash 
gtk-demo
```
