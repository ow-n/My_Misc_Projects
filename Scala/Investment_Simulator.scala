// Investment Simulator

import scala.util.Random

object InvestmentSimulator {
  var annualIncome = 100000.00 // $100,000
  val incomeGrowthRate = 0.01
  val savingsContributionRate = 0.40
  val durationOfSimulation = 40

  // Define constants for the investment return rates
  val savingsBankReturnRate = (1.025, 0.95) // Tuple (good year, bad year)
  val sp500ReturnRate = (1.08, 0.80)
  val techStockReturnRate = (1.15, 0.60)
  val dividendStockReturnRate = (1.03, 0.99)

  // User Bank Details
  var savingsAcc = 40000.00   // #1 $40,0000 Starting Savings
  var sP500 = 0.00          // #2
  var techAcc = 0.00        // #3
  var diviAcc = 0.00        // #4

  // Global Variables
  var numBullYrs = 0
  var numBearYrs = 0
  var isRecession = true
  val random = new Random()

  // Deposit Methods
  def bankDepositInto(investmentType: Int, capital: Double): Boolean = {
    if (capital > savingsAcc) {
      println("\nNot enough money in Savings Account to transfer")
      false // this is trippy
    } else {
      savingsAcc -= capital
      investmentType match {
        case 2 => sP500 += capital
        case 3 => techAcc += capital
        case 4 => diviAcc += capital
      }
      println(f"Net Worth:\nBank: $$${savingsAcc}%.2f\nS&P500: $$${sP500}%.2f\nTech: $$${techAcc}%.2f\nDividend: $$${diviAcc}%.2f")
      true
    }
  }

  def smp500DepositInto(investmentType: Int, capital: Double): Boolean = {
    if (capital > sP500) {
      println("\nNot enough money in S&P 500 Account to transfer")
      false
    } else {
      sP500 -= capital
      investmentType match {
        case 1 => savingsAcc += capital
        case 3 => techAcc += capital
        case 4 => diviAcc += capital
      }
      println(f"Net Worth:\nBank: $$${savingsAcc}%.2f\nS&P500: $$${sP500}%.2f\nTech: $$${techAcc}%.2f\nDividend: $$${diviAcc}%.2f")
      true
    }
  }

  def techDepositInto(investmentType: Int, capital: Double): Boolean = {
    if (capital > techAcc) {
      println("\nNot enough money in Tech Account to transfer")
      false
    } else {
      techAcc -= capital
      investmentType match {
        case 1 => savingsAcc += capital
        case 2 => sP500 += capital
        case 4 => diviAcc += capital
      }
      println(f"Net Worth:\nBank: $$${savingsAcc}%.2f\nS&P500: $$${sP500}%.2f\nTech: $$${techAcc}%.2f\nDividend: $$${diviAcc}%.2f")
      true
    }
  }

  def diviDepositInto(investmentType: Int, capital: Double): Boolean = {
    if (capital > diviAcc) {
      println("\nNot enough money in Dividend Account to transfer")
      false
    } else {
      diviAcc -= capital
      investmentType match {
        case 1 => savingsAcc += capital
        case 2 => sP500 += capital
        case 3 => techAcc += capital
      }
      println(f"Net Worth:\nBank: $$${savingsAcc}%.2f\nS&P500: $$${sP500}%.2f\nTech: $$${techAcc}%.2f\nDividend: $$${diviAcc}%.2f")
      true
    }
  }

  // Other Methods
  def calcRecession(): Unit = {
    val chanceOfRecessionEnd = math.max(0.10 * (numBearYrs - 1), 0) // 10% Base Chance Recession End after 1 Yr
    val chanceOfRecessionStart = math.max(0.10 * (numBullYrs - 6), 0) // 10% Base Chance Recession Start after 6 Yr

    if (isRecession) {
      numBearYrs += 1
      // Increasing Random Chance: Does Recession End?
      if (numBearYrs > 2 && random.nextDouble() < chanceOfRecessionEnd) {
        isRecession = false
        println("\nRecession has ended.")
      }
    } else {
      numBullYrs += 1
      // Increasing Random Chance: Does Recession Start? (After 7 Yrs Bull)
      if (numBullYrs > 7 && random.nextDouble() < chanceOfRecessionStart) {
        isRecession = true
        println("\nRecession has started.")
      }
    }
    // Reset counters when recession status changes
    if (isRecession != (numBearYrs > 0)) {
      numBullYrs = 0
      numBearYrs = 0
    }
  }

  def calcAnnualReturns(): Unit = {
    calcRecession()
    savingsAcc *= (if (isRecession) savingsBankReturnRate._2 else savingsBankReturnRate._1)
    sP500 *= (if (isRecession) sp500ReturnRate._2 else sp500ReturnRate._1)
    techAcc *= (if (isRecession) techStockReturnRate._2 else techStockReturnRate._1)
    diviAcc *= (if (isRecession) dividendStockReturnRate._2 else dividendStockReturnRate._1)
  }

  def main(args: Array[String]): Unit = {
    println("This is an Investment Simulator")
    println(f"You are earning $$${annualIncome}%.2f and manage to save ${savingsContributionRate * 100}%% of it. Your income will increase by ${incomeGrowthRate * 100}%% each year.")
    println("\nAnything you do that MAY break the program WILL break the program")
    println("NO EXCEPTIONS. NO EDGE CASES. NO HANDLING. -no time :(") // no time :(

    for (year <- 1 to durationOfSimulation) {
      println(s"\nYear $year")
      println(f"Net Worth:\nBank: $$${savingsAcc}%.2f\nS&P500: $$${sP500}%.2f\nTech: $$${techAcc}%.2f\nDividend: $$${diviAcc}%.2f")

      var reallocate = true
      while (reallocate) {
        println("\nDo you want to reallocate your net worth?")
        println("1. Bank deposit into...")
        println("2. SP deposit into...")
        println("3. Tech deposit into...")
        println("4. Dividend deposit into...")
        println("5. Next year")

        val choice = scala.io.StdIn.readInt()
        choice match {
          case 1 | 2 | 3 | 4 => handleReallocationChoice(choice)
          case 5 => reallocate = false
          case _ => println("Invalid option. Please enter a number from 1 to 5.")
        }
      }

      // Every Year:
      calcAnnualReturns()
      annualIncome *= (1 + incomeGrowthRate)
      savingsAcc += (annualIncome * savingsContributionRate)
    }

    // Display final results
    println("\nSimulation complete. Final net worth:")
    println(f"Bank: $$${savingsAcc}%.2f\nS&P500: $$${sP500}%.2f\nTech: $$${techAcc}%.2f\nDividend: $$${diviAcc}%.2f")
  }

  def handleReallocationChoice(fromAccount: Int): Unit = {
    println("\nSelect the account to deposit into: (don't pick the illegal one)")
    println("1. Bank")
    println("2. S&P500")
    println("3. Tech")
    println("4. Dividend")
  
    val toAccount = scala.io.StdIn.readInt()
    var amount = 0.0
  
    do {
      println("\nEnter Amount: (0 to exit)")
      amount = scala.io.StdIn.readDouble()
      if (amount > 0) {
        fromAccount match {
          case 1 => bankDepositInto(toAccount, amount)
          case 2 => smp500DepositInto(toAccount, amount)
          case 3 => techDepositInto(toAccount, amount)
          case 4 => diviDepositInto(toAccount, amount)
          case _ => println("Invalid option.")
        }
        amount = 0
      }
    } while (amount != 0)
  }
}