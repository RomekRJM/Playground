package main

import (
	"fmt"
	"strconv"
)

type Player struct {
	firstName string
	lastName  string
	age       uint8
}

func getName() {
	_, err := fmt.Scan(&name)
	if err != nil {
		return
	}

	fmt.Printf("Type: %T\n", name)
	fmt.Println("Length:", len(name))
}

func makeMyMap() {
	var myMap = make(map[string]string)
	myMap["foo"] = strconv.FormatUint(23, 2)
	myMap["goo"] = "balls"
}

func arrayStruct() {
	var player = Player{
		firstName: "Beep",
		lastName:  "Boop",
		age:       uint8(16),
	}

	var playerMap = make([]Player, 1)
	playerMap = append(playerMap, player)

	fmt.Println(playerMap)
}
