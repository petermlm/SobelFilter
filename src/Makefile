# Copyright 2018 Pedro Melgueira
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

FILES=main.c sobel.c file_operations.c
OBJS=$(FILES:.c=.o)
ARQUIVE=libsobel.a
EXE=sobel
FLAGS=-std=c99 -g -lm

all: $(OBJS) archive
	gcc $(OBJS) -o $(EXE) $(FLAGS)

.c.o:
	gcc -c $< -o $@ $(FLAGS)

archive:
	ar rcs $(ARQUIVE) $(OBJS)

clean:
	rm $(OBJS) $(ARQUIVE) $(EXE)

