# Markdown 语法参考

-----

章节:
<font face="Console" size=4>

  [1.注释方式](#Commentary)
  [2.设定背景颜色](#ResetBackGroundColor)
  [3.富文本编辑](#RichTextEdit)
  [4.绘画表格](#DrawTableView)
  [5.设置超链接](#Linkage)

</font>
-----

<span id=Commentary><!--语法点一 : 如何注释--></span>

## 注释方式 
  <!--我是注释-->
  <div style="Display:None">我也是注释</div>

  [](我是注释)

  - html风格注释
    ```markdown
      <!--注释-->
    ``` 
  - html样式实现隐藏(不推荐)
    ```html
      <div style="Display:None">注释本体</div>
    ``` 
  - markdown隐藏标记(不推荐)
    ```markdown
      [](注释本体)
    ```

<span id=ResetBackGroundColor><!--语法点二 : 修改背景颜色--></span>

## 整体背景颜色的更改

- 实现整体背景颜色的更改可以应用语句:
  
  ```markdown
      <style> body { background-color:rgb(...) ! important } </style> 
  ```

<span id=RichTextEdit><!--语法点三 : 富文本编辑--></span>

## 富文本编辑
[字体详解(B站)](https://www.bilibili.com/read/cv5975926/)

- 富文本编辑可以使用html font 语法
  ``` markdown
    <font [face=""] [size=] [color]> </font>
  ``` 
  如使用以下语句
  ``` markdown
    <font face="楷体" size=3 color=rgb(23,13,73)>Raw</font>
  ``` 
  得到以下结果 ：
    <font face="楷体" size=3 color=rgb(23,13,73)>Raw</font>

<span id=DrawTableView><!--语法点四 : 如何画表格--></span>

## 画表格
- 利用markdown内部语法画表格

  ```markdown
    |周数|周一|周二|周三|周四|周五|周六|周日|总结|
    |---|---|---|---|---|---|---|---|---|
    |第一周|√|√|√|√|√|/|/|按时完成|
    |第二周|√|√|×|×|×|/|/|进行中|
    |第三周|||||||
    |第四周|||||||
  ```
  示例结果:
  
  |周数|周一|周二|周三|周四|周五|周六|周日|总结|
  |---|---|---|---|---|---|---|---|---|
  |第一周|√|√|√|√|√|/|/|按时完成|
  |第二周|√|√|×|×|×|/|/|进行中|
  |第三周|||||||
  |第四周|||||||

- 利用html 表格语法画表格
  <font face="楷体">

    表格主体
    ```markdown
      <table>
        <tbody>

        </tbody>
      </table>
    ```
    `<tr></tr>` : 创建单元格
    `<th></th>` : 标记标题
    `<td [bgcolor=]></td>` : 标记表格内容

  </font>

<span id=Linkage><!--语法点五 : 设置超链接--></span>

## 链接
  `[]()`  : 链接
  `![]()` : 显示

- 图片链接格式
  <font face="楷体">

  ```markdown
    ![图片标题](url)  
  ```

  示例:
    `代码:`
    ```markdown 
      ![示例图片显示在这](./RES/PatrickStarPout.gif)`
    ```

    ![示例图片显示在这](./RES/PatrickStarPout.gif)

  </font>

- 页面跳转:
  <font face="楷体">

  直接使用`[Title](url)`

  </font>

- 同文件位置跳转
  <font face="楷体">
      同页面跳转利用跳转标记`[](#)` 以及html`<span>`语法实现定向跳转

  ```markdown
    <!--跳转起始处-->
    [点这里跳转](#跳转的ID)
    ...

    <span id=跳转的ID>画面跳转到了这里</span>
  ```

  </font>





