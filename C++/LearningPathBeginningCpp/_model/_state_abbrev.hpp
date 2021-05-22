/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   _state_abbrev.hpp
 * Author: roman.subik
 *
 * Created on 15 listopada 2017, 07:23
 */

#ifndef _STATE_ABBREV_HPP
#define _STATE_ABBREV_HPP

enum class StateAbbrev {
    AL, AK, AZ, AR,
    CA, CO,
    DE,
    FL,
    GA,
    HI,
    ID, IL, IN, IA,
    KS, KY,
    LA,
    ME, MD, MA, MI, MN, MS, MO, MT,
    NE, NV, NH, NJ, NM, NY, NC, ND,
    OH, OK, OR,
    PA,
    RI,
    SC, SD,
    TN, TX,
    UT, VT, VA,
    WA, WV, WI, WY,
    UNKNOWN
};

const std::string stateNames[50] = {"Alabama","Alaska","Arizona",
  "Arkansas","California","Colorado"," Connecticut",
  "Delaware","Florida","Georgia","Hawaii","Idaho",
  "Illinois","Indiana","Iowa","Kansas","Kentucky",
  "Louisiana","Maine","Maryland","Massachusetts",
  "Michigan","Minnesota","Mississippi","Missouri",
  "Montana","Nebraska","Nevada","New Hampshire",
  "New Jersey","New Mexico","New York","North Carolina",
  "North Dakota","Ohio","Oklahoma","Oregon",
  "Pennsylvania","Rhode Island","South Carolina",
  "South Dakota","Tennessee","Texas","Utah",
  "Vermont","Virginia","Washington","West Virginia",
  "Wisconsin","Wyoming"};

StateAbbrev to_abbrev(const std::string stateName) {
    int i = 0;
    for (auto s : stateNames) {
        if (s == stateName) {
            return static_cast<StateAbbrev>(i);
        }
    }
    
    return StateAbbrev::UNKNOWN;
}

#endif /* _STATE_ABBREV_HPP */

