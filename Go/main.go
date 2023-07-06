package main

import (
	"fmt"
	"learning/pack"
	"strings"
)

// these are package level variables
var u8 uint8 = 127
var name string

func main() {
	var a = "!"
	// equivalent to a := "!"

	const constantVal = 50

	fmt.Println("Hello world", a)
	fmt.Printf("Constant: %v\n", constantVal)

	pack.GoRoutineTest()

	getName()

	var anArray [50]string = [50]string{"foo1 foo2", "bar1 bar2", "bam1"}
	anArray[3] = "bom"

	fmt.Println("array:", anArray)

	_, _ = getFirstPartOfStringArray(anArray)

	var slice []uint8 = []uint8{}
	slice = append(slice, u8)

	fmt.Println(slice)

	pack.SwitchTest()

	makeMyMap()

	arrayStruct()
}

func getFirstPartOfStringArray(anArray [50]string) (int, string) {
	noElements := 0

	for index, value := range anArray {
		fields := strings.Fields(value)

		if len(fields) > 0 {
			fmt.Println("fields:", fields[0], "index:", index)
			noElements += 1
		}
	}

	return noElements, "You can return multiple values from Go function"

}
