// Weighted Food Critique Caclulator

use std::io;

fn main() {
    let categories = ["Taste", "Value", "Nutrition", "Presentation", "Service"];
    let weights = [1.0, 1.6, 1.4, 0.3, 0.2]; // <-- Personalize Your Weights
    let mut ratings = [0.0; 5];

    println!("Give ratings out of 100.");

    let mut index = 0;
    loop {
        if index >= ratings.len() {
            break;
        }
        println!("{} Rating: ", categories[index]);
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        ratings[index] = input.trim().parse::<f32>().expect("Invalid Number");
        index += 1;
    }

    let overall_rating = calculate_overall_rating(&ratings, &weights);
    println!("\nOverall Rating: {}/100", overall_rating);
    
    let ratings_summary = create_ratings_summary(&categories, &ratings);
    println!("\nRatings Summary:\n{}", ratings_summary);
}

fn calculate_overall_rating(ratings: &[f32; 5], weights: &[f32; 5]) -> f32 {
    let mut weighted_rating_sum = 0.0;
    let mut total_weight = 0.0;

    for i in 0..ratings.len() {
        weighted_rating_sum += ratings[i] * weights[i];
        total_weight += weights[i];
    }

    let average_score = weighted_rating_sum / total_weight;
    let overall_rating = average_score.round() as f32;

    overall_rating
}

fn create_ratings_summary(categories: &[&str; 5], ratings: &[f32; 5]) -> String {
    let mut summary = String::new();
    let mut i = 0;
    while i < categories.len() {
        summary.push_str(&format!("{}: {}\n", categories[i], ratings[i]));
        i += 1;
    }
    summary
}