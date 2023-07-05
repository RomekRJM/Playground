package main

import "fmt"

func main() {
	var a = "!"
	// equivalent to a := "!"

	const constantVal = 50

	fmt.Println("Hello world", a)
	fmt.Printf("Constant: %v\n", constantVal)

	var name string

	fmt.Scan(&name)

	fmt.Printf("Type: %T\n", name)
	fmt.Println("Length:", len(name))

	var anArray [50]string = [50]string{"foo", "bar", "bam"}
	anArray[3] = "bom"

	fmt.Println("array:", anArray)

	var slice []uint8 = []uint8{}
	slice = append(slice, 123)

	fmt.Println(slice)
}
