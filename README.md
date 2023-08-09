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
