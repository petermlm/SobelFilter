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

all:
	cd src && make
	cd tests && make

check:
	cd tests && make check

run:
	convert imgs/img.png imgs/img.rgb
	./src/sobel imgs/img.rgb imgs/img_out.gray 512x512 -g imgs/img_out_gray.gray -i imgs/img_out_h.gray imgs/img_out_v.gray
	convert -size 512x512 -depth 8 imgs/img_out.gray imgs/img_out.png
	convert -size 512x512 -depth 8 imgs/img_out_gray.gray imgs/img_out_gray.png
	convert -size 512x512 -depth 8 imgs/img_out_h.gray imgs/img_out_h.png
	convert -size 512x512 -depth 8 imgs/img_out_v.gray imgs/img_out_v.png

clean:
	cd src && make clean
	cd tests && make clean

clean_run:
	rm imgs/img_out* imgs/img.rgb

