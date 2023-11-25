make

❯ sudo insmod yark.ko
[sudo] black 的密码：
❯ tree /sys/kernel/yark/
/sys/kernel/yark/
├── give_root
│   ├── give
│   └── giveme
├── hide_file
│   ├── add
│   ├── del
│   └── list
├── hide_module
│   └── vis
├── hide_port
│   ├── add
│   ├── del
│   └── list
├── hide_proc
│   ├── add
│   ├── del
│   └── list
└── protect_proc
    ├── add
    ├── del
    └── list
