import UIKit

class Button {
    let height: Double
    let width: Double
    let color: UIColor
    let symbol: String
    init(height: Double, width: Double, color: UIColor, symbol: String){
        self.height = height
        self.width = width
        self.color = color
        self.symbol = symbol
    }
    convenience init(side: Double, color: UIColor, symbol: String) {
        self.init(height: side, width: side, color: color, symbol: symbol)
    }
}

let oneButton = Button(height: 2.5, width: 2.5, color: .gray, symbol: "1")
let twoButton = Button(height: 2.5, width: 2.5, color: .gray, symbol: "2")
let equalButton = Button(height: 2.5, width: 2.5, color: .blue, symbol: "=")
let plusButton = Button(height: 6, width: 6, color: .blue, symbol: "+")



