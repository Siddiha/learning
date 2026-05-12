package main

import "fmt"

func add(a int, b int) int {
	return a + b
}

func main() {
	var name string
	var age int

	fmt.Print("Enter your name: ")
	fmt.Scanln(&name)

	fmt.Print("Enter your age: ")
	fmt.Scanln(&age)

	if age >= 18 {
		fmt.Println("Hello", name, "you are an adult")
	} else {
		fmt.Println("Hello", name, "you are a minor")
	}

	//slice
	numbers := []int{1, 2, 3, 4, 5}
	fmt.Println("Numbers in slice:")

	//Loop
	for _, num := range numbers {
		fmt.Println(num)
	}

	//function call
	result := add(10, 5)
	fmt.Println("10 + 5 =", result)
	fmt.Println("\nCountdown:")

	for i := 5; i >= 1; i-- {
		fmt.Println(i)
	}
}
