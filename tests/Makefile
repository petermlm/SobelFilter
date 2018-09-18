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

SOURCES=some.c
ARQUIVE=../src/libsobel.a
EXE=check_sobel
FLAGS=-lcheck

all:
	gcc $(SOURCES) $(ARQUIVE) -o $(EXE) $(FLAGS)

check:
	./$(EXE)

clean:
	rm $(EXE)

