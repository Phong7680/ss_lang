#
# Makefile ... コンパイルに使うファイルの依存関係
#

# make によるコンパイル
#       make           … 更新したファイルだけをコンパイル
#       make clean     … オブジェクトファイルと実行ファイルを削除
#       make cleanall  … 生成した全ファイルを削除

# 生成するファイルの名前の指定 (必要に応じて変更)
TOKEN = base.o tokenizer.o
EVALUATOR = base.o tokenizer.o parser.o tree.o evaluator_hatten.o environment.o

#######################################################################
# 通常，以下は書き換え不要

# 生成する全ファイル名の指定
ALLOBJ = $(EVALUATOR) evaluator.o a1.o a2.o a3.o a4.o b1.o b2.o b3.o b4.o c1.o c2.o ss.o
ALLEXE = a1 a2 a3 a4 b1 b2 b3 b4 c1 c2 ss
ALLTXT = a1.txt a2.txt a3.txt a4.txt b1.txt b2.txt b3.txt b4.txt c1.txt c2.txt c3.txt c4.txt comment.txt

# nhom cac file cung loai 

# コンパイラの指定

CC     = gcc
CFLAGS = -Wall -W    # 全ての警告を表示

# 全ファイルを作る規則

all: $(ALLTXT)

# テキストファイルを作る規則

a1.txt: a1
	- ./a1 > $@
a2.txt: a2
	- ./a2 > $@
a3.txt: a3
	- ./a3 > $@
a4.txt: a4
	- ./a4 > $@
b1.txt: b1
	- ./b1 > $@
b2.txt: b2
	- ./b2 > $@
b3.txt: b3
	- ./b3 > $@
b4.txt: b4
	- ./b4 > $@
c1.txt: c1
	- ./c1 > $@
c2.txt: c2
	- ./c2 > $@
c3.txt: ss
	- ./ss program1.ss > $@
c4.txt: ss
	- ./ss program2.ss> $@
comment.txt: ss
	- ./ss comment.ss> $@

# レポートファイルを作る規則
rp:
	platex report.tex
	platex report.tex
	dvipdfmx report.dvi

# 実行ファイルを作る規則
a1: $(TOKEN) a1.o
	$(CC) $(CFLAGS) $^ -o $@
a2: $(TOKEN) a2.o
	$(CC) $(CFLAGS) $^ -o $@
a3: $(TOKEN) a3.o
	$(CC) $(CFLAGS) $^ -o $@
a4: $(TOKEN) a4.o
	$(CC) $(CFLAGS) $^ -o $@

b1: base.o tree.o b1.o
	$(CC) $(CFLAGS) $^ -o $@
b2: $(TOKEN) parser.o tree.o b2.o
	$(CC) $(CFLAGS) $^ -o $@
b3: base.o tokenizer.o parser.o tree.o evaluator.o b3.o
	$(CC) $(CFLAGS) $^ -o $@
b4: $(EVALUATOR) b4.o
	$(CC) $(CFLAGS) $^ -o $@

c1: $(EVALUATOR) c1.o
	$(CC) $(CFLAGS) $^ -o $@
c2: $(EVALUATOR) c2.o
	$(CC) $(CFLAGS) $^ -o $@
ss: $(EVALUATOR) ss.o
	$(CC) $(CFLAGS) $^ -o $@

# オブジェクトファイルを作る規則

.SUFFIXES: .h .c .o

.h.c:
		touch $*.c

.c.o:
		$(CC) $(CFLAGS) -c $<

# ファイルを消す規則

clean:
		rm -f $(ALLEXE) $(ALLOBJ)

cleanall:
		rm -f $(ALLEXE) $(ALLOBJ) $(ALLTXT)
