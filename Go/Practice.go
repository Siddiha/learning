import "fmt"

func add(a int, b int) int  {
	return a + b
}

func main(){
	var name string
	var age int

	fmt.print("Enter your name: ")
	fmt.scaln(&name)

	fmt.print("Enter your age: ")
	fmt.scanln(&age)

	if age >= 18 {
		fmt.println("hello", name, "you are an adult")
	}else{
		fmt.println("Hello", name, "you area minor")
	}

	//slice
	numbers := []int{1, 2, 3, 4, 5}
	fmt.println("/Number in slice:")

	//Loop
	for _, num := range numbers {
		fmt.println(num)
	}

	//function call
	result := add(10, 5)
	fmt.println("10 + 5=", result)
	 fmt.Println("\nCountdown:")

	 for i := 5 ; i >= 1 ; i--{
		fmt.println(i)
	 }
}