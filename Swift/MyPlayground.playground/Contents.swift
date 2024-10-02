import UIKit
var greeting = "Hello, playground"
print(greeting)
2 + 2
let one = 1
var res = 1
res = res + 20
var n: Int = 20
var name = ""
let first = "Egor"
let second = "Legend"
name = first + " " + second
print(name)
var number: Int? = 0
var a: Int = 1
let b = 2
let result = a > b ? "!!!!!" : ">>>>>"
if -4 < a {
    print("1")
} else {
    print("+")
}
var x: String? = "212121"
if let text = x {
    print("text")
}
let UserInput = 0
switch UserInput{
case ..<0:
    print("Neg")
case 0:
    print("Zero")
default:
    print("Pos")
}



let ab = 5
let ba = ab == 5 ? 2 : 4
switch ba {
case 1:
    print("H")
case 4:
    print("W")
default:
    print("S")
}

func greeting(for userName: String = "Alex", with age: Int = 20) {
    print("Hello \(userName) with age")
}

greeting(with: 10)


