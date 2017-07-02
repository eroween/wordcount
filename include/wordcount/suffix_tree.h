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

#ifndef     __WORDCOUNT_SUFFIX_TREE_H__
#define     __WORDCOUNT_SUFFIX_TREE_H__

#include    <stdbool.h>
#include    <stdio.h>

///
/// \brief a suffix tree node.
///
typedef struct  suffix_tree_node
{
    ///
    /// \brief next contain a bunch of pointer for the next word char.
    ///
    struct suffix_tree_node   *next[127];

    ///
    /// \brief counter contain a counter for a word.
    ///
    unsigned long long int  counter;
} suffix_tree_node;

///
/// \brief suffix_tree_build_from_dict_file build a suffixicographic tree from a dictionary file.
/// \param filepath the filepath that lead to a dictionary file.
/// \param callback an error callback, used to report specific error.
/// \return a null pointer to a suffixicographic tree if something failed, the parent node
/// of a suffixicographic tree otherwise.
///
/// parsing error are avoided and the callback is called with an error message.
///
suffix_tree_node   *suffix_tree_build_from_dict_file(const char *filepath);

///
/// \brief suffix_tree_build_from_dict_stream build a suffixicographic tree from a stream.
/// \param stream the stream that contain the dictionary data.
/// \param callback an error callback, used to report specific error.
/// \return a null pointer to a suffixicographic tree if something failed, the parent node
///
/// parsing error are avoided and the callback is called with an error message.
///
suffix_tree_node   *suffix_tree_build_from_dict_stream(FILE *stream);

///
/// \brief suffix_tree_add_word add a word to a suffixicographic tree.
/// \param suffix_tree the suffix_tree that we must add a word to.
/// \param word the word that will be added to the suffix_tree.
/// \return true if everything worked, false otherwise.
///
/// add a word to a suffixicographic doesnt increment the number of word.
///
bool    suffix_tree_add_word(suffix_tree_node *suffix_tree, const char *word);

///
/// \brief suffix_tree_inc_word increment the count number of a word.
/// \param suffix_tree the suffixicographic tree where we will increment a word counter.
/// \param word the word that must be inc.
/// \return true if the inc succeeded, false otherwise.
///
/// return false if the word doesnt exist.
///
bool    suffix_tree_inc_word(suffix_tree_node *suffix_tree, const char *word);

///
/// \brief suffix_tree_print print a suffixicographic tree on the standard output stream.
/// \param suffix_tree the suffix_tree that must be printed.
///
void    suffix_tree_print(suffix_tree_node *suffix_tree);

///
/// \brief suffix_tree_free free a suffix tree.
/// \param suffix_tree the suffix tree that must be freed.
///
void    suffix_tree_free(suffix_tree_node *suffix_tree);

#endif // !__WORDCOUNT_LEX_TREE_H__
