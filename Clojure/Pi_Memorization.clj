; Memorize 200 Digits of Pi

(def pi-seq "3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214810555964462294895493038196")

(defn check-pi [current-seq user-input]
  (let [new-seq (str current-seq user-input)
        input-length (count new-seq)
        pi-substr (subs pi-seq 0 input-length)]
    (= new-seq pi-substr)))

(defn print-hints [n]
  (let [hints (for [i (range n)] (subs pi-seq i (+ i 1)))]
    (doseq [hint hints]
      (println (str "Hint: " hint)))))

(defn pi-game []
  (println "Memorize 200 digits of Pi!")
  (let [hints (vec (for [i (range 3)] (subs pi-seq i (+ i 1))))]
    (loop [current-seq ""
           attempts 1
           incorrect-attempts []]
      (println (str "\nAttempt: " attempts))
      (println (str "Current Pi: " current-seq))
      (println "Enter the next digit(s) of Pi:")
      (let [user-input (read-line)
            correct (check-pi current-seq user-input)
            next-three (subs pi-seq (count current-seq) (+ (count current-seq) 3))]
        (if correct
          (recur (str current-seq user-input) attempts (conj incorrect-attempts user-input))
          (do
            (println "\nIncorrect! Starting over.")
            (println "The next three digits were: " next-three)
            (println "---------------------------\n")
            (recur "" (+ attempts 1) (conj incorrect-attempts user-input))))))))

(defn review-incorrect-attempts [incorrect-attempts]
  (when-not (empty? incorrect-attempts)
    (do
      (println "Review of your incorrect attempts:")
      (doseq [attempt incorrect-attempts]
        (println attempt)))))

(defn start-game []
  (let [result (pi-game)]
    (review-incorrect-attempts (nth result 2))
    (println "Game Over!")))

(start-game)