//
// MIT License
//
// Copyright(c) 2016 - 2017 Martin - Pierrat Louis(louismartinpierrat@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include    "wordcount/wordcount.h"
#include    "wordcount/suffix_tree.h"

#define     IS_VALID_CHAR(X)    (X >= 33 && X <= 126)

static void wordcount_count_word_from_stream(suffix_tree_node *suffix_tree, FILE *stream)
{
    // we need an iterator to move through the tree.
    suffix_tree_node    *it = suffix_tree;
    int     c = 0;

    while((c = fgetc(stream)) != EOF && IS_VALID_CHAR(c))
    {
        if (it->next[c] == NULL)
        {
            it = NULL;
            break;
        }
        it = it->next[c];
    }
    // if we found a word.
    if (it != NULL && it->next['\0'] != NULL)
    {
        it->next['\0']->counter += 1;
    }
}

void    wordcount_on_stream(suffix_tree_node *suffix_tree, FILE *stream)
{
    int     c = 0;

    // read until the end of the file.
    while((c = fgetc(stream)) != EOF)
    {
        if (IS_VALID_CHAR(c) == false)
        {
            continue;
        }
        ungetc(c, stream);
        wordcount_count_word_from_stream(suffix_tree, stream);
    }

}

void    wordcount_on_files(suffix_tree_node *suffix_tree, const int number_of_file,
                           const char *filenames[])
{
    for (int i = 0 ; i < number_of_file ; ++i)
    {
        FILE *filestream = fopen(filenames[i], "r");

        if (filestream == NULL)
        {
            fprintf(stderr, "[ERR] filename : \"%s\" cannot be opened.\n", filenames[i]);
            continue;
        }
        wordcount_on_stream(suffix_tree, filestream);
        fclose(filestream);
    }
}
