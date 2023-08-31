# What is this project?( これはどのようなプロジェクト？ )
crepは"CREate Project"を略した名称である。

crep stands for "CREate Project".

## Background( このプロジェクトの問題意識 )
他の言語ではどうか分からないが、少なくともC++言語では、
プロジェクトを作るたびに必要な定型的な操作がある。

それは例えば、特定のディレクトリ構造を作ったり、
cmakeファイルを作ったすることだ。
プロジェクトや人によっては、最初はREADME.mdを作ったり、
LISENCE.mdを作ることから始めるかもしれない。
好みの.clang-formatを最初に作りたいと考えている人もいることだろう。
人や、そのプロジェクトの思想によって具体的な操作は様々だろうが、
最初に定型的な操作が必要だということには同意していただけるだろう。
そして、その操作によって作られたもの(例えばディレクトリ構造や、
cmakeファイル、README.md、LISENCE.md、.clang-formatなど)は、
プロジェクトの進行に伴って変更することもあるかもしれない。
しかし、プロジェクトの開始時点では、
どのプロジェクトでも似たり寄ったりなものとなるだろう。

そこで、そのような定型的な操作を簡単に済ませられるようなプログラムを作りたい。

I don't know about other languages, but at least with C++, there are some boilerplate operations that need to be done every time you create a project.

For example, creating a specific directory structure or creating a cmake file. Depending on the project and people, you might start by creating a README.md or a LISENCE.md. Some of you may want to create your preferred .clang-format first. The specific operations will vary depending on the person and the philosophies of the project, but you will agree that a standard operation is necessary first. And what is created by that operation (for example, directory structure, cmake file, README.md, LISENCE.md, .clang-format, etc.) may change as the project progresses. However, at the beginning of a project, all projects will be more or less the same.

Therefore, I would like to create a program that can easily perform such routine operations.

## Purpose( このプロジェクトが提供したいもの )
このプロジェクトの目的は、プロジェクトに共通した定型的な
操作という手間を、できる限り省くことにある。

ただし、このプロジェクトの目的は、万人に共通の開始点を作り出すことではないし、
プロジェクトを開始した人達が「どの開始点を選ぶか」と議論できるような共通言語を作りだすことでもない。

もちろん、そのようなことが起こっても一向に構わない。
しかし、仮にそのようなことが起こったとしても、
それはあくまでも副次的なものであって、
このプロジェクトの目標とすることではない。

このプロジェクトの目的は偏にプロジェクトの作成を補助することであり、
それ以上でもそれ以下でもない。

The purpose of this project is to avoid the routine operations common to projects as much as possible.

And the purpose of this project is not to create a common starting point for everyone, nor to create a common language in which people who start a project can argue about which starting point to choose.

Of course, it doesn't matter if that happens. However, even if such a thing were to happen, it would only be secondary and not the goal of this project.

The purpose of this project is to help create projects, nothing more, nothing less.

## Realization method( 実現手段 )
crepを実行して得られるものを、プロジェクトの開始点、あるいは単に開始点と呼ぶことにしよう。
つまりプロジェクトの開始点とは、ある特定のディレクトリ構造を持ったファイル群のことだ。

プロジェクトの開始点を作る方法は大きく2つ存在する。
一つは、スクリプトによってプロジェクトの開始点を生成するという方法だ。
もう一つは、テンプレートをどこかに保存しておいて、
それをプロジェクトを作りたいディレクトリ(多くの場合は、カレントディレクトリであろう)に
コピーするという方法だ。

この内、私は(私の考え方が変わらない限り)後者の方法を取りたい。

その理由は2つある。
1つ目は、スクリプトによる制御を行った場合、
プロジェクトの開始点がどのようなものとなるかが分かりづらいことだ。
2つ目は、実際に生成しない限り、コンパイルが不可能だというとだ。

1つ目の理由は明らかだろう。
プロジェクトはできる限り簡単に作れるべきであると考えている。
プロジェクトの作成を簡単にすることが、crepの目的であるのに、
プロジェクトを作ることが一つのプロジェクトとなってしまう程に
大変になるのは本末転倒だからである。それは、私の最も避けたいことだ。

2つ目の理由としては、最初の状態でコンパイルできないのであれば、
それはプロジェクトを作成した後、コンパイルできるようにするまで、
ある程度以上の作業が必要になるということだ。
それはcrepが目的を達成できていないということに他ならない。

また、そのような状態はプロジェクトの開始点にすでにエラー、
あるいはバグが存在する状態だと言えるだろう。
それはもはや、様々なプロジェクトに転移するガンだ。
赤子が何の病気も持たずに生まれてくることが望ましいのと同じように、
プロジェクトも何の病気も持たずに生まれることが望ましいだろう。
その一番の方法は、生成されたプロジェクトの開始点にエラーが存在するかどうかを確かめるというものだ。
その簡単で、確実な方法は、開始点をコンパイルしてみるというものだろう。
テンプレート形式の場合、そのテンプレート自身をコンパイルすればよい。
テンプレート自体がプロジェクトの開始点だからだ。
しかし、スクリプトによって開始点を生成する場合、
実際にコンパイルするためには、crepによって開始点を作らなければならない。
この2つの方法を比べた場合、テンプレートをコピーした方が
ユーザにとって便利であると考えられる。

以上より、(現状の)基本的な方針としては、
プロジェクトのテンプレートを作成して、
そのテンプレートをコピーするという方法を採りたい。

しかしこの方法を採用すると、ファイルの内容を細かく制御することが
難しくなってしまうかもしれない。
また、スクリプト形式を採用したときよりも容量が大きくなってしまう可能性が高いという問題もある。

Let's call what you get from running crep the starting point, or just the starting point, of your project. So the starting point of a project is a set of files with a certain directory structure.

There are two main ways to create a starting point for your project. One way is to generate a starting point for the project with a script. Another way is to save the template somewhere and copy it to the directory where you want to create the project (in most cases it will be the current directory).

Of these, I prefer the latter method (unless my thinking changes).

There are two reasons. First, it's hard to know what the starting point of a project would look like with scripting control. The second is that it's impossible to compile unless you actually generate it.

The first reason should be obvious. We believe that projects should be as easy to create as possible. The purpose of crep is to make project creation easy, but creating a project becomes so difficult that it becomes a single project. That's the last thing I want to do.

The second reason is that if you can't compile the project in the first place, you'll need to do some more work after creating the project to get it to compile. It is nothing but that crep has not achieved its purpose.

Also, such a state can be said to be a state where an error or bug already exists at the beginning of the project. It is no longer a cancer that spreads to various projects. Just as it would be desirable for a baby to be born without any disease, it would be desirable for a project to be born without any disease. The best way to do this is to see if there are any errors at the start of the generated project. An easy and surefire way to do that would be to try compiling a starting point. In the case of template format, the template itself can be compiled. The template itself is the starting point of the project. However, if you generate the starting point with a script, you must create the starting point with a crep in order to actually compile. Comparing these two methods, it is considered that copying the template is more convenient for the user.

From the above, as a basic policy (currently), I would like to adopt a method of creating a project template and copying that template.

However, this method may make it difficult to control the contents of the file finely. There is also the problem that the capacity is likely to become larger than when the script format is adopted.

# How to use this software?( このソフトウェアを使うには？ )
## How to install?( インストール方法 )
いずれ簡単にインストールできる方法も作ろうとは考えているが、
ひとまず基本機能を作ることを優先しているため、
今はまだ簡単にインストールできるような方法は作っていない。

このプログラムを利用したければ、現状ではソースコードからビルドしていただくより他にない。

次の節のいずれかのコマンドを実行すると、
プロジェクトルートに新しくbuild/というディレクトリが作られる。
そのbuild/以下の/src/crepというファイルが実行ファイルとなっている。
crepを他のコマンドと同じく、"crep"とコマンドラインに入力しただけで実行してほしければ、
<project_root>/build/src/というディレクトリを環境変数に登録すればいい
(ただし、<project_root>は人によって様々だろうから、適宜自分の環境に合わせて読み変えてほしい)。
もしくは、環境変数に登録されているディレクトリに、
<project_root>/build/src/crepへのリンクを作ればいい。

## How to build this project?
### If you want to use libstdc++( libstdc++を利用してビルドしたい場合 )
cmake -Dslib=libstdc++ -P build.cmake
もしくは、
cmake -P build.cmake

### If you want to use libc++( libc++を利用してビルドしたい場合 )
cmake -Dslib=libc++ -P build.cmake

## ビルド時の注意事項
このソフトウェアは、Ubuntu 22.04LTS上では問題なく動作することを確認している。
しかし、他の環境でも動作するかどうかは分からない。
