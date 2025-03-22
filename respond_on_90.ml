type card = Seven | Eight | Nine | Ten | Jack | Queen | King | Ace

let is_9 c = match c with Nine -> true | _ -> false

let to_string c =
        match c with 
        | Seven -> "Seven"
        | Eight -> "Eight"
        | Nine -> "Nine"
        | Ten -> "Ten"
        | Jack -> "Jack"
        | Queen -> "Queen"
        | King -> "King"
        | Ace -> "Ace"


let deal_part_hand _ = 
        let remaining_cards = [ Seven ; Queen ; Ace ; Nine ] in
        let starting_hand : card list = [] in
        let add_one_card hand card =
                let player = Random.int 3 in
                if player = 1 then
                        card :: hand
                else
                        hand
        in
        List.fold_left add_one_card starting_hand remaining_cards


let count_raise should_raise count part_hand =
        if should_raise part_hand then
                count + 1
        else
                count


let any_9second part_hand =
        match part_hand with
        | []
        | [_] -> false
        | [ Nine; _ ] -> true
        | [ _ ; Nine ] -> true
        | [ a; b ] -> false
        | _ 
        -> true

let () =
        Random.self_init ();
        let lazy_hands = Seq.init 1_000_000 deal_part_hand in
        let count = Seq.fold_left  (count_raise (List.exists is_9))  0 lazy_hands in
        Format.printf "Num raises on 9 only: %d@." count;

        let lazy_hands = Seq.init 1_000_000 deal_part_hand in
        let count = Seq.fold_left  (count_raise any_9second)  0 lazy_hands in
        Format.printf "Num raises on 9 second or more: %d@." count;
