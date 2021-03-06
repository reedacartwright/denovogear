/*
 * Copyright (c) 2017 Reed A. Cartwright
 * Authors:  Reed A. Cartwright <reed@cartwrig.ht>
 *
 * This file is part of DeNovoGear.
 *
 * DeNovoGear is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#ifndef DNG_LIBRARY_H
#define DNG_LIBRARY_H

#include <vector>
#include <string>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/erase.hpp>

#include <dng/detail/graph.h>

namespace dng {

struct libraries_t {
    std::vector<std::string> names;
    std::vector<std::string> samples;
};

#define DNG_LABEL_PREFIX_GERMLINE "GL"
#define DNG_LABEL_PREFIX_SOMATIC  "SM"
#define DNG_LABEL_PREFIX_LIBRARY  "LB"
#define DNG_LABEL_SEPARATOR "/"
#define DNG_LABEL_SEPARATOR_CHAR '/'

// Remove Prefixes from Sample/Library Labels
template<typename S>
S trim_label_prefix(const S &input) {
    using boost::starts_with;
    using boost::erase_head_copy;

	if(starts_with(input, (DNG_LABEL_PREFIX_LIBRARY DNG_LABEL_SEPARATOR))) {
        return erase_head_copy(input, strlen((DNG_LABEL_PREFIX_LIBRARY DNG_LABEL_SEPARATOR)));
    } else if(starts_with(input, (DNG_LABEL_PREFIX_GERMLINE DNG_LABEL_SEPARATOR))) {
		return erase_head_copy(input, strlen((DNG_LABEL_PREFIX_GERMLINE DNG_LABEL_SEPARATOR)));
	} else if(starts_with(input, (DNG_LABEL_PREFIX_SOMATIC DNG_LABEL_SEPARATOR))) {
		return erase_head_copy(input, strlen((DNG_LABEL_PREFIX_SOMATIC DNG_LABEL_SEPARATOR)));
	}
    return input;
}

// Return an empty label for germline and somatic prefixes
// Remove label for library prefix
template<typename S>
S trim_label_prefix_only_libraries(const S &input) {
    using boost::starts_with;
    using boost::erase_head_copy;

    if(starts_with(input, (DNG_LABEL_PREFIX_GERMLINE DNG_LABEL_SEPARATOR))) {
        return {};
    } else if(starts_with(input, (DNG_LABEL_PREFIX_SOMATIC DNG_LABEL_SEPARATOR))) {
        return {};
    } else if(starts_with(input, (DNG_LABEL_PREFIX_LIBRARY DNG_LABEL_SEPARATOR))) {
        return erase_head_copy(input, strlen((DNG_LABEL_PREFIX_LIBRARY DNG_LABEL_SEPARATOR)));
    }
    return input;
}


}

#endif // DNG_LIBRARY_H
