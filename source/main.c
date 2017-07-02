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
#include    "wordcount/wordcount.h"

#include    <time.h>

///
/// \brief main entry point of the program
/// \param argc the number of arguments of the program.
/// \param argv an array of program argument.
/// \return 0 if everything worked, non-zero otherwise.
///
int     main(const int argc, const char *argv[])
{
    if (argc < 2)
    {
        fprintf(stdout, "Usage : ./wordcount dictionary_file [input_file ...]\n");
        return 0;
    }

    clock_t vartime = clock();
    suffix_tree_node   *suffix_tree = suffix_tree_build_from_dict_file(argv[1]);
    long building_time = clock() - vartime;

    if (suffix_tree == NULL)
    {
       fprintf(stderr, "[ERR] the suffixicographic tree can't be created.\n");
       return 1;
    }

    vartime = clock();
    // case where we must only count word on standard input stream.
    if (argc == 2)
    {
        wordcount_on_stream(suffix_tree, stdin);
    }
    else
    {
        // we skip the program name and the dictionary file argument.
        wordcount_on_files(suffix_tree, argc - 2, argv + 2);
    }
    long wordcount_time = clock() - vartime;

    vartime = clock();
    suffix_tree_print(suffix_tree);
    long print_time = clock() - vartime;

    vartime = clock();
    suffix_tree_free(suffix_tree);
    long free_time = clock() - vartime;

    fprintf(stdout, "datastructure building time : %f\n", (double)(building_time) / CLOCKS_PER_SEC);
    fprintf(stdout, "wordcount time : %f\n", (double)(wordcount_time) / CLOCKS_PER_SEC);
    fprintf(stdout, "print time : %f\n", (double)(print_time) / CLOCKS_PER_SEC);
    fprintf(stdout, "datastructure freeing time : %f\n", (double)(free_time) / CLOCKS_PER_SEC);
    return 0;
}
