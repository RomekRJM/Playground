/*
 * data.hpp
 *
 *  Created on: Jul 21, 2015
 *      Author: dubchak
 */

#ifndef DATA_HPP_
#define DATA_HPP_

#include <iomanip>
#include <memory>
#include <string>
#include <map>

constexpr auto STATE_POS = 6;
constexpr std::size_t START_IDX = 0;
constexpr std::size_t END_IDX = 49;
constexpr std::size_t US_STATES = 50;

auto states = std::unique_ptr<std::string[]>(new std::string[US_STATES]);
auto frequencies = std::map<std::string, int>();


inline void initialize() {

    states[0] = "Alabama";
    states[1] = "Alaska";
    states[2] = "Arizona";
    states[3] = "Arkansas";
    states[4] = "California";
    states[5] = "Colorado";
    states[6] = "Connecticut";
    states[7] = "Delaware";
    states[8] = "Florida";
    states[9] = "Georgia";
    states[10] = "Hawaii";
    states[11] = "Idaho";
    states[12] = "Illinois";
    states[13] = "Indiana";
    states[14] = "Iowa";
    states[15] = "Kansas";
    states[16] = "Kentucky";
    states[17] = "Louisiana";
    states[18] = "Maine";
    states[19] = "Maryland";
    states[20] = "Massachusetts";
    states[21] = "Michigan";
    states[22] = "Minnesota";
    states[23] = "Mississippi";
    states[24] = "Missouri";
    states[25] = "Montana";
    states[26] = "Nebraska";
    states[27] = "Nevada";
    states[28] = "New Hampshire";
    states[29] = "New Jersey";
    states[30] = "New Mexico";
    states[31] = "New York";
    states[32] = "North Carolina";
    states[33] = "North Dakota";
    states[34] = "Ohio";
    states[35] = "Oklahoma";
    states[36] = "Oregon";
    states[37] = "Pennsylvania";
    states[38] = "Rhode Island";
    states[39] = "South Carolina";
    states[40] = "South Dakota";
    states[41] = "Tennessee";
    states[42] = "Texas";
    states[43] = "Utah";
    states[44] = "Vermont";
    states[45] = "Virginia";
    states[46] = "Washington";
    states[47] = "West Virginia";
    states[48] = "Wisconsin";
    states[49] = "Wyoming";

    frequencies["Alabama"] = 0;
    frequencies["Alaska"] = 0;
    frequencies["Arizona"] = 0;
    frequencies["Arkansas"] = 0;
    frequencies["California"] = 0;
    frequencies["Colorado"] = 0;
    frequencies["Connecticut"] = 0;
    frequencies["Delaware"] = 0;
    frequencies["Florida"] = 0;
    frequencies["Georgia"] = 0;
    frequencies["Hawaii"] = 0;
    frequencies["Idaho"] = 0;
    frequencies["Illinois"] = 0;
    frequencies["Indiana"] = 0;
    frequencies["Iowa"] = 0;
    frequencies["Kansas"] = 0;
    frequencies["Kentucky"] = 0;
    frequencies["Louisiana"] = 0;
    frequencies["Maine"] = 0;
    frequencies["Maryland"] = 0;
    frequencies["Massachusetts"] = 0;
    frequencies["Michigan"] = 0;
    frequencies["Minnesota"] = 0;
    frequencies["Mississippi"] = 0;
    frequencies["Missouri"] = 0;
    frequencies["Montana"] = 0;
    frequencies["Nebraska"] = 0;
    frequencies["Nevada"] = 0;
    frequencies["New Hampshire"] = 0;
    frequencies["New Jersey"] = 0;
    frequencies["New Mexico"] = 0;
    frequencies["New York"] = 0;
    frequencies["North Carolina"] = 0;
    frequencies["North Dakota"] = 0;
    frequencies["Ohio"] = 0;
    frequencies["Oklahoma"] = 0;
    frequencies["Oregon"] = 0;
    frequencies["Pennsylvania"] = 0;
    frequencies["Rhode Island"] = 0;
    frequencies["South Carolina"] = 0;
    frequencies["South Dakota"] = 0;
    frequencies["Tennessee"] = 0;
    frequencies["Texas"] = 0;
    frequencies["Utah"] = 0;
    frequencies["Vermont"] = 0;
    frequencies["Virginia"] = 0;
    frequencies["Washington"] = 0;
    frequencies["West Virginia"] = 0;
    frequencies["Wisconsin"] = 0;
    frequencies["Wyoming"] = 0;
}

void increment(const std::string& state) {
	frequencies[state] += 1;
}

#endif /* DATA_HPP_ */
