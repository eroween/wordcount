
## ASSETS

dictionary_light.txt = 18 unique word.
dictionary_medium.txt = 29.024 unique word.
dictionary.txt = 235.886 unique word.

input_light.txt = 18 unique word.
input_medium.txt = 29.024 unique word.
input.txt = 235.886 unique word.

## RESULT

Usage : ./wordcount ./assets/dictionary_medium.txt ./assets/input_medium.txt \
    ./assets/input.txt ./assets/input_light.txt ./assets/input.txt \
    ./assets/input.txt ./assets/input.txt ./assets/input_medium.txt

-> dictionary : 29.024 unique word.
-> input : 1.001.610 words

datastructure building time : 0.354153
wordcount time : 0.245516
print time : 0.079602
datastructure freeing time : 0.051144

405.205 total word.

-----

usage : ./wordcount ./assets/dictionary.txt ./assets/input_medium.txt \
    ./assets/input.txt ./assets/input_light.txt ./assets/input.txt \
    ./assets/input.txt ./assets/input.txt ./assets/input_medium.txt

-> dictionary : 235.886 unique word.
-> input : 1.001.610 words

datastructure building time : 2.859859
wordcount time : 0.376825
print time : 0.644839
datastructure freeing time : 0.375413

1.001.610 total words

## Implementation

generalized suffix tree - naive implementation

don't require size limitation for dictionary word neither for stream word.

I made some assumptions :

	- memory is not important
	- building time is not important
	- counting word timing IS important
	- word overlap really often. (like in the english dictionary)

So I choose to use a suffix tree in order to count word as fast as I can. And I also wanted to implement that. :D
	
## Implementation time

The code has been writed, fully debugged and tested in approximatively 3h30.

tested on Ubuntu 16.04 (gcc 5.4.0) and Windows 10 (VC15)

## Area of improvements

- Better API for suffix tree
- Use a more advanced implementation of a suffix tree, like a radix tree can be a good idea.
- the code is not cache efficient.
- Multithreading can be a way to optimize counting word on multiple stream.
- reduce the memory usage...
- unicode support... (only ascii char has been tested, can be easy to add UTF8 but not UTF16 or UTF32). (we can also convert UTF16/32 stream to UTF8 and support only UTF8.
- ...
