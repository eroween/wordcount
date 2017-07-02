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

#ifndef     __WORDCOUNT_WORDCOUNT_H__
#define     __WORDCOUNT_WORDCOUNT_H__

#include    "wordcount/suffix_tree.h"

#include    <stdio.h>

///
/// \brief wordcount_on_stream count the word present in a stream.
/// \param suffix_tree a suffixicographic tree that store the word.
/// \param stream the stream that we must use to count word.
///
void    wordcount_on_stream(suffix_tree_node *suffix_tree, FILE *stream);

///
/// \brief wordcount_on_files count the number of word present in an array of files.
/// \param suffix_tree the suffixicographic tree that will contain the count of every files.
/// \param number_of_file the number of filenames present in the filenames array.
/// \param filenames the array of filename.
///
void    wordcount_on_files(suffix_tree_node *suffix_tree, const int number_of_file, const char *filenames[]);

#endif // !__WORDCOUNT_WORDCOUNT_H__
