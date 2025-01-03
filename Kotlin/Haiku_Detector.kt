// ============================= //
// { Unreliable Haiku Detector } //
// ============================= //

/* Working Haikus:
"Quick, someone go to all OSU games and start posting on YouTube"
    - r/MichiganWolverines, ecw324
"People stand faster than this stuff because this is Nokia on wheels"
    - r/RoatMyCar, KOTWWA_K
"This is probably the most heated post I had ever seen on here"
    - r/RedDeadRedemption, MasterChiefDoomGuy */

fun main() {
    // modern coding -> local variable scoping?? :(
    println("Who's the poet? ")
    val name = readLine() ?: ""

    var isValid = false
    val userWords = mutableListOf<String>()
    val lineWordCounts: IntArray = intArrayOf(0, 0)
    do {
        println("\nShow me your art: ")
        var userHaiku = readLine() ?: ""
        println("\n[Detected: \"$userHaiku\"]\n") // [DEBUG]

        userWords.clear()
        userHaiku = userHaiku.trim()
        userWords.addAll(userHaiku.lowercase().split(" "))
        if (isValidHaiku(userWords, lineWordCounts)) isValid = true
        else println("That was beautiful, but it wasn't a Haiku.\n")
    } while (isValid == false)

    println("Legit Haiku, Now Processing:") // [DEBUG]
    var formattedHaiku = formatHaiku(userWords, lineWordCounts)
    println("Your haiku is:")
    println(formattedHaiku)
    println("- $name")
}

fun isValidHaiku(words: MutableList<String>, lineWordCounts: IntArray): Boolean {
    var currSyllableCount = 0
    var prevSyllableCount = 0

    println("Syllables Per Word: ") // [DEBUG]
    for (word in words) {
        prevSyllableCount = currSyllableCount
        currSyllableCount += countSyllables(word)

        // False if syllable of words goes to over to next line
        if (prevSyllableCount < 5 && currSyllableCount > 5 ||
            prevSyllableCount < 12 && currSyllableCount > 12) {
            println("Curr: $currSyllableCount, Prev: $prevSyllableCount\n")
            println("Syllables spilled over to next line")
            return false
        }

        if (currSyllableCount <= 5) lineWordCounts[0]++
        if (currSyllableCount > 5 && currSyllableCount <= 12) lineWordCounts[1]++
    }

    println("Curr: $currSyllableCount, Prev: $prevSyllableCount\n")
    if (currSyllableCount != 17) return false
    return true
}

/* Diphthongs: Two Vowels, One Syllable
 * rain, day, eat, see, pie, boat, toe, oil, boot, house, blue, suit */

// Impossible Challenge:
fun countSyllables(userHaiku: String): Int {
    val vowels = setOf('a', 'e', 'i', 'o', 'u', 'y')
    val diphthongs = setOf("ai", "ay", "ea", "ee", "ie", "oa", "oe", "oi", "oo", "ou", "ue", "ui")
    var syllableCount = 0
    var prevCharIsVowel = false // no longer used

    var i = 0
    while (i < userHaiku.length) {
        var currentChar = userHaiku[i]
        if (currentChar in vowels) { // if vowel
            // Check for diphthongs
            if (i + 1 < userHaiku.length) { // if not last char
                var nextChar = userHaiku[i + 1]
                var potentialDiphthong = "" + currentChar + nextChar
                if (potentialDiphthong in diphthongs) { // if diphthong
                    syllableCount++
                    i += 2
                    prevCharIsVowel = true
                    continue
                }
            } // Vowel but Not Diphthong
            prevCharIsVowel = true
            syllableCount++
            i++
        } else { // Not Vowel
            prevCharIsVowel = false
            i++
        }
    }

    // Special Case: Words ending in 'e'
    if (userHaiku.endsWith('e') && userHaiku.length > 2) {
        val secondToLastCharNotVowel = userHaiku[userHaiku.length - 2] !in vowels
        val thirdToLastCharNotVowel = if (userHaiku.length > 3) userHaiku[userHaiku.length - 3] !in vowels
                                      else false
        val notADiphthong = !(userHaiku.length > 3 &&
                              userHaiku.substring(userHaiku.length - 3, userHaiku.length - 1) in diphthongs)

        if (secondToLastCharNotVowel && (thirdToLastCharNotVowel || syllableCount > 1)) {
            // println("-1 syllable 'e': 2ndLast!vowel + 3rdLast!vowel/syll>1'") // [DEBUG]
            syllableCount--

            if (notADiphthong) {
                // println("-1 syllable 'e': !diphthong") // [DEBUG]
                syllableCount--
            }
        }
    }

    // Special Case: 'le' at the end, but only if it's preceded by a consonant
    if (userHaiku.endsWith("le") &&
        userHaiku.length > 2 &&
        userHaiku[userHaiku.length - 3] !in vowels) {
        syllableCount++
    }

    // Special Case: Words with no vowels
    if (syllableCount == 0) syllableCount++

    print("$syllableCount, ") // [DEBUG]]
    return syllableCount
}

fun formatHaiku(words: MutableList<String>, lineWordCounts: IntArray): String {
    var haiku = StringBuilder()
    var wordsIndex = 0

    // Line 1
    for (i in 0 until lineWordCounts[0]) {
        val word = if (i == 0) capitalizeFirstChar(words[wordsIndex++])
        else words[wordsIndex++] // :)
        haiku.append(word).append(" ")
    }
    haiku.append("\n")

    // Line 2
    for (i in 0 until lineWordCounts[1]) {
        val word = if (i == 0) capitalizeFirstChar(words[wordsIndex++])
        else words[wordsIndex++]
        haiku.append(word).append(" ")
    }
    print("$wordsIndex, ") // [DEBUG]
    haiku.append("\n")

    // Line 3
    var isStartingIndex = true
    while (wordsIndex < words.size) {
        val word = if (isStartingIndex) {
            isStartingIndex = false
            capitalizeFirstChar(words[wordsIndex++])
        }
        else words[wordsIndex++]
        haiku.append(word)
        if (wordsIndex < words.size) haiku.append(" ")
    }
    print("$wordsIndex\n\n") // [DEBUG]

    return haiku.toString()
}

fun capitalizeFirstChar(word: String): String {
    if (word.isEmpty()) return word
    val firstChar = word[0].uppercaseChar()
    return firstChar + word.substring(1)
}