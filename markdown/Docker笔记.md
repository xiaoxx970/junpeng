# Docker note

> Use Docker without root
>
> https://docs.docker.com/install/linux/linux-postinstall/
>
> ```sh
> sudo groupadd docker
> sudo usermod -aG docker $USER
> newgrp docker
> ```

## docker container

- 列出正在运行的容器:
    ```
    docker ps
    ```
    
- 列出所有容器:
    ```
    docker ps -a
    ```
    
- 执行容器中的命令:
    ```
    docker (container) run --name <name> alpine ls
    ```

    在alpine镜像作的容器中执行`ls`，然后输出到控制台，然后结束自己。

    加`--rm`可以让容器在退出之后删除，默认情况下，为了排障需求，退出的容器并不会立即删除，除非手动 `docker rm`。
    
    > 每次通过镜像名运行的容器都是互相隔离的，里面的文件修改也是。
    
- 开启一个容器：
    ```sh
    docker (container) start <container id|name>
    ```

    这时候用`docker container ls`就可以看到正在运行的容器，每个容器前面都有一个`CONTAINER ID`，可以通过ID指定要执行命令的容器

- 在开启的容器中执行命令
    ```sh
    docker (container) exec <container id|name> ls
    ```

    这里和run是不一样的,`exec`指定容器ID来执行命令,且必须在container运行中才可以执行。之前对这个容器的修改都会保留。

- 进入到一个容器中
    ```sh
    docker (container) exec -it <container id|name> /bin/bash
    ```

- 接入到一个容器中

    ```sh
    docker attach <container id|name>
    ```

    > Detach from container use`CTRL-p` `CTRL-q`

- 删除一个容器
    ```sh
    docker (container) rm <container id|name>
    ```
    
- 删除所有停止的容器

    ```sh
    docker container prune
    ```
    
- 停止所有容器

    ```sh
    docker stop $(docker ps -a -q)
    ```
    
- 创建一个我自己的容器

    在run了一个容器后，我对里面的内容进行了改变，想要把我的改变打包成一个新的容器，就用commit：
    ```
    docker container commit <container id|name>
    ```
    commit以后，在`docker image ls`中可以看到刚commit的容器镜像

    `docker image tag <IMAGE_ID> ourfiglet`可以给我的镜像取名


## docker image

- 列出本机所有镜像
    ```sh
    docker image ls
    ```
    
- 删除所有没用过的镜像

    ```sh
    docker image prune
    ```
    
- 删除所有当前没在运行的镜像

    ```sh
    docker image prune -a
    ```

- docker pull
    - 下载镜像到本机
        ```
        docker pull [选项] [Docker Registry 地址[:端口号]/]仓库名[:标签]
        ```


## Dockerfile

一个强大的docker定义文件，类似于travis的yml文件，里面指定需要的运行环境，变量，以及要执行的指令。
- 建立一个`index.js`文件,里面写这个
    ```js
    var os = require("os");
    var hostname = os.hostname();
    console.log("hello from " + hostname);
    ```
    
- 建立一个`Dockerfile`文件,里面写这个
    ```dockerfile
    FROM alpine
    RUN apk update && apk add nodejs
    COPY . /app
    WORKDIR /app
    CMD ["node","index.js"]
    ```

- 编译 `Dockerfile` 

  ```sh
  docker build .
  ```

- 使用

  在`docker image ls`中可以看到刚建立的容器镜像

  `docker image tag <IMAGE_ID> newname`可以给我的镜像取名

![](https://training.play-with-docker.com/images/ops-images-dockerfile.svg)

在这里，Dockerfile 叫 docker做了这些事情：

1. 指定基础镜像，这里使用 `alpine`。
2. 运行两条命令 (apk update 和 apk add) 在容器内安装了 Node.js server。
3. 然后可以告诉它复制当前目录的文件到容器内，当前只有一个文件被复制：index.js。
4. 然后我们指定工作目录——容器开启时所在的目录。
5. 最后，给容器一个命令 (CMD) 当开启时运行。