# 项目结构
- catkin_ws  (总项目文件夹)
  - build (编译文件)
  - devel (开发工具文件, 里面有个setup.bash经常会用)
  - install (用不到)
  - src (!!源码)
    - build (编译的代码)
    - learning_topic
      - build
      - msg
        - 用来放置自定义的消息类型
        - xxx.msg
      - include
        - xxx.h
        - xxx.h
        - ...
      - src
        - xxx.cpp
        - xxx.cpp
        - ...
    - test_pkg
    - 各种功能包......