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

#include    "wordcount/suffix_tree.h"
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>

#define     IS_VALID_CHAR(X)    (X >= 33 && X <= 126)

static suffix_tree_node     *suffix_tree_build_empty_node(void)
{
    suffix_tree_node    *node = malloc(sizeof(suffix_tree_node));

    if (node != NULL)
    {
        for (int i = 0 ; i < sizeof(node->next) / sizeof(node->next[0]) ; ++i)
            node->next[i] = NULL;
        node->counter = 0;
    }
    return node;
}

static suffix_tree_node     *suffix_tree_add_letter(suffix_tree_node *node, unsigned char c)
{
    if ((IS_VALID_CHAR(c) == false && c != '\0') || node == NULL)
    {
        return NULL;
    }

    // if the char havent been added to the tree yet.
    if (node->next[c] == NULL)
    {
        // build a node for it.
        node->next[c] = suffix_tree_build_empty_node();
        if (node->next[c] == NULL)
        {
            return NULL;
        }
    }
    return node->next[c];
}

static bool     suffix_tree_add_word_from_stream(suffix_tree_node *suffix_tree, FILE *stream)
{
    // we need an iterator to move through the tree.
    suffix_tree_node    *it = suffix_tree;
    int     c = 0;

    fprintf(stderr, "building tree, adding word : \"");
    // read one word and add it to the suffix_tree.
    while((c = fgetc(stream)) != EOF && IS_VALID_CHAR(c))
    {
        fprintf(stderr, "%c", c);
        // add a letter in the suffix tree node.
        it = suffix_tree_add_letter(it, c);
        if (it == NULL)
        {
            return false;
        }
    }
    // if we have new char in the tree.
    if (it != suffix_tree)
    {
        // add an end of word char.
        suffix_tree_add_letter(it, '\0');
        fprintf(stderr, "\".\r");
    }
    // skip the until the end of the line.
    while (c != '\n' && (c = fgetc(stream)) != EOF);
    return true;
}

static void     suffix_tree_build(suffix_tree_node *suffix_tree, FILE *stream)
{
    int     c = 0;
    unsigned long long int  num_of_word_add = 0;

    // read until the end of the file.
    while((c = fgetc(stream)) != EOF)
    {
        // avoid commentary line.
        if (c == '#')
        {
            while ((c = fgetc(stream)) != EOF && c != '\n');
            continue;
        }

        // avoid empty line.
        if (c == '\n')
        {
            continue;
        }

        // we have a valid word to read and add to the suffix_tree.
        ungetc(c, stream);
        suffix_tree_add_word_from_stream(suffix_tree, stream);
        ++num_of_word_add;
    }
    fprintf(stderr, "number of word added to the tree : %lld\n", num_of_word_add);
}

suffix_tree_node   *suffix_tree_build_from_dict_file(const char *filepath)
{
    FILE    *filestream = fopen(filepath, "r");
    suffix_tree_node   *suffix_tree = NULL;

    if (filepath == NULL || filestream == NULL)
    {
        fprintf(stderr, "[ERR] the dictionary file : \"%s\" cannot be opened.\n", filepath);
        return NULL;
    }

    suffix_tree = suffix_tree_build_from_dict_stream(filestream);
    fclose(filestream);
    return suffix_tree;
}

suffix_tree_node   *suffix_tree_build_from_dict_stream(FILE *stream)
{
    if (stream == NULL)
    {
        return NULL;
    }

    // we build the root node of the suffix tree.
    suffix_tree_node    *suffix_tree = suffix_tree_build_empty_node();

    if (suffix_tree != NULL)
    {
        suffix_tree_build(suffix_tree, stream);
    }
    return suffix_tree;
}

bool    suffix_tree_add_word(suffix_tree_node *suffix_tree, const char *word)
{
    if (suffix_tree == NULL || word == NULL)
    {
        return false;
    }
    return false;
}

bool    suffix_tree_inc_word(suffix_tree_node *suffix_tree, const char *word)
{
    if (suffix_tree == NULL || word == NULL)
    {
        return false;
    }

    return false;
}

static void     suffix_tree_print_word(suffix_tree_node *node,
                                       unsigned long long int *total_word,
                                       char **word_buffer, size_t index,
                                       size_t *word_buffer_length)
{
    if (node == NULL || word_buffer == NULL)
    {
        return;
    }

    // if we need to reallocate the word_buffer.
    if (index + 1 >= *word_buffer_length)
    {
        word_buffer_length += sizeof(char) * 255;
        *word_buffer = realloc(*word_buffer, *word_buffer_length);
        if (*word_buffer == NULL)
        {
            return;
        }
    }

    // if we have an end_of_word char.
    if (node->next['\0'] != NULL)
    {
        (*word_buffer)[index] = '\0';
        fprintf(stdout, "%lld %s\n", node->next['\0']->counter, *word_buffer);
        *total_word += node->next['\0']->counter;
    }

    for (int i = 1 ; i < sizeof(node->next) / sizeof(node->next[0]) ; ++i)
    {
        if (node->next[i] != NULL)
        {
            (*word_buffer)[index] = i;
            suffix_tree_print_word(node->next[i], total_word, word_buffer, index + 1, word_buffer_length);
        }
    }
}

void    suffix_tree_print(suffix_tree_node *suffix_tree)
{
    if (suffix_tree == NULL)
    {
        return;
    }

    size_t  word_buffer_length = sizeof(char) * 255;
    char    *word_buffer = malloc(word_buffer_length);
    unsigned long long int  total_word = 0;

    if (word_buffer == NULL)
    {
        fprintf(stderr, "[ERR] memory allocation failed.");
        return;
    }

    for (int i = 1 ; i < sizeof(suffix_tree->next) / sizeof(suffix_tree->next[0]) ; ++i)
    {
        if (suffix_tree->next[i] != NULL)
        {
            word_buffer[0] = i;
            suffix_tree_print_word(suffix_tree->next[i], &total_word, &word_buffer, 1, &word_buffer_length);
        }
    }
    fprintf(stdout, "%lld total word\n", total_word);
    free(word_buffer);
}

void    suffix_tree_free(suffix_tree_node *suffix_tree)
{
    if (suffix_tree == NULL)
    {
        return;
    }

    for (int i = 0 ; i < sizeof(suffix_tree->next) / sizeof(suffix_tree->next[0]) ; ++i)
    {
        suffix_tree_free(suffix_tree->next[i]);
    }

    free(suffix_tree);
}
