type card = Sept | Huit | Neuf | Dix | Valet | Dame | Roi | As

let is_9 c = match c with Neuf -> true | _ -> false

let to_string c =
        match c with 
        | Sept -> "Sept"
        | Huit -> "Huit"
        | Neuf -> "Neuf"
        | Dix -> "Dix"
        | Valet -> "Valet"
        | Dame -> "Dame"
        | Roi -> "Roi"
        | As -> "As"


let deal_part_hand _ = 
        (* I have V 10 R 8 *)
        let remaining_cards = [ Sept ; Dame ; As ; Neuf ] in
        let starting_hands : card list array = [|[]; []; []|] in
        let add_one_card hands card =
                let player = Random.int 3 in
                match player with 
                | 0 -> [|card :: (Array.get hands 0) ; (Array.get hands 1) ; (Array.get hands 2)|]
                | 1 -> [|(Array.get hands 0) ; card :: (Array.get hands 1) ; (Array.get hands 2)|]
                | 2 -> [|(Array.get hands 0) ; (Array.get hands 1) ; card :: (Array.get hands 2)|]
                | _ -> [|[]; []; []|]
        in
        let final_hands = List.fold_left add_one_card starting_hands remaining_cards  in
        let part_hand = (Array.get final_hands 1) in
        part_hand


let count_raise should_raise count part_hand =
        if should_raise part_hand then
                count + 1
        else
                count


let any_9second part_hand =
        match part_hand with
        | []
        | [_] -> false
        | [ Neuf; _ ] -> true
        | [ _ ; Neuf ] -> true
        | [ a; b ] -> false
        | _ 
        -> true

let () =
        Random.self_init ();
        let lazy_hands = (Seq.init 1_000_000 deal_part_hand) in
        let count = Seq.fold_left  (count_raise (List.exists is_9))  0 lazy_hands in
        Format.printf "Num raises on 9 only: %d@." count;
        let count = Seq.fold_left  (count_raise any_9second)  0 lazy_hands in
        Format.printf "Num raises on 9 second or more only: %d@." count;
