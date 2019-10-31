- docker container

    - 列出正在运行的容器:
        ```
        docker container ls
        ```
    - 列出所有容器:
        ```
        docker container ls -a
        ```
    - 执行容器中的命令:
        ```
        docker (container) run --name <name> alpine ls
        ```
        在alpine镜像作的容器中执行`ls`，然后输出到控制台，然后结束自己。

        加`--rm`可以让容器在退出之后删除，默认情况下，为了排障需求，退出的容器并不会立即删除，除非手动 `docker rm`。
        > 每次通过镜像名运行的容器都是互相隔离的，里面的文件修改也是。
    - 开启一个容器：
        ```
        docker (container) start <container id|name>
        ```
        这时候用`docker container ls`就可以看到正在运行的容器，每个容器前面都有一个`CONTAINER ID`，可以通过ID指定要执行命令的容器
    - 在开启的容器中执行命令
        ```
        docker (container) exec <container id|name> ls
        ```
        这里和run是不一样的,`exec`指定容器ID来执行命令,且必须在container运行中才可以执行。之前对这个容器的修改都会保留。
    - 进入到一个容器中
        ```
        docker (container) exec -it <container id|name> /bin/bash
        ```
    - 删除一个容器
        ```
        docker (container) rm <container id|name>
        ```
    - 创建一个我自己的容器

        在run了一个容器后，我对里面的内容进行了改变，想要把我的改变打包成一个新的容器，就用commit：
        ```
        docker container commit <container id|name>
        ```
        commit以后，在`docker image ls`中可以看到刚commit的容器镜像
        
        `docker image tag <IMAGE_ID> ourfiglet`可以给我的镜像取名
- docker image
    - 列出本机所有镜像
        ```
        docker image ls
        ```
- docker pull
    - 下载镜像到本机
        ```
        docker pull [选项] [Docker Registry 地址[:端口号]/]仓库名[:标签]
        ```
- Dockerfile

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
    ![](https://training.play-with-docker.com/images/ops-images-dockerfile.svg)
    - Dockerfile叫docker做了这些事情：
        1. Specifies a base image to pull FROM - the alpine image we used in earlier labs.
        2. Then it RUNs two commands (apk update and apk add) inside that container which installs the Node.js server.
        3. Then we told it to COPY files from our working directory in to the container. The only file we have right now is our index.js.
        4. Next we specify the WORKDIR - the directory the container should use when it starts up
        5. And finally, we gave our container a command (CMD) to run when the container starts.