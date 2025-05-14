---
description: how to use linux patch
---

# patch

#### **1. `patch` 基本用法**

**应用补丁**

bash复制下载

```
patch -pNUM < patch_file
```

* **`-pNUM`**：剥离补丁文件中的路径前缀层级。\
  例如：若补丁中的路径是 `a/src/file.c`，当前目录下有 `src/file.c`，则用 `-p1` 剥离 `a/`。

**常用选项**

* **`-i <file>`**：指定补丁文件。
* **`-R`**：撤销已应用的补丁。
* **`-b`**：备份原始文件（生成 `.orig` 文件）。
* **`--dry-run`**：模拟应用补丁（不修改文件）。

**示例**

bash复制下载

```
# 应用补丁，剥离一级路径前缀，并备份原文件
patch -p1 -b < changes.patch

```

#### **2. 使用 `patch --merge` 生成冲突标记（类似 Git）**

`patch` 的 `--merge` 选项会直接在目标文件中插入**冲突标记**（`<<<<<<<` 和 `>>>>>>>`），类似 Git 的冲突提示，便于定位和解决。

**操作步骤**

bash复制下载

```
# 应用补丁并生成冲突标记
patch -p1 --merge < changes.patch
```

**冲突文件示例**

c复制下载

```
int main() {
<<<<<<< original
    printf("Hello World\n");
    return 0;
=======
    printf("Hello Linux\n");
    return 1;
>>>>>>> changes.patch
}
```

* **`<<<<<<< original`**：当前文件的内容。
* **`=======`**：分隔符。
* **`>>>>>>> changes.patch`**：补丁中试图修改的内容。

**解决方法**

1. 打开冲突文件（如 `main.c`）。
2. 根据需求选择保留 `original`（当前内容）或 `changes.patch`（补丁内容），或手动合并两者。
3. 删除所有冲突标记（`<<<<<<<`, `=======`, `>>>>>>>`）。
4.  保存文件后，重新运行 `patch` 验证是否成功：

    bash复制下载

    ```
    patch -p1 < changes.patch
    ```

\
