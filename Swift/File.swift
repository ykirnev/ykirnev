func fib(a: Int) -> Int {
    if a <= 2 {
        return 1
    }
    return fib(a: a - 1) + fib(a: a - 2)
}

if let input = readLine(), let n = Int(input) {
    let result = fib(a: n)
    print(result)
}

