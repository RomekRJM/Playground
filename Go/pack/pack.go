package pack

import (
	"fmt"
	"sync"
	"time"
)

// City this is a global variable in Go, as it starts with uppercase
var City string = "New York"

// SwitchTest if function name starts with uppercase, it is exported outside package
func SwitchTest() {
	switch City {
	case "New York", "Tampa":
		fmt.Println("In US")
	case "London":
		fmt.Println("In UK")
	}
}

var Wg = sync.WaitGroup{}

func GoRoutineTest() {
	Wg.Add(1)
	go print1()

	fmt.Println("########## 2")

	Wg.Wait()
}

func print1() {
	time.Sleep(6 * time.Second)
	fmt.Println("########## 1")
	Wg.Done()
}
