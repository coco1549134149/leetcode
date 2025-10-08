#!/bin/bash
echo "=== Git 远程仓库检查 ==="
git remote -v

echo -e "\n=== 网络连通性检查 ==="
ping -c 2 github.com

echo -e "\n=== SSH 连接测试 ==="
ssh -T git@github.com

echo -e "\n=== 仓库访问测试 ==="
timeout 10 git ls-remote origin

echo -e "\n=== 分支状态 ==="
git status --short --branch

echo -e "\n=== 诊断完成 ==="
