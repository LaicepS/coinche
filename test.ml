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


let deal_one_hand _ = 
        Random.self_init ();
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
        if List.length  part_hand > 0 then
                Format.printf "Cards card: %s@." (to_string (List.nth part_hand 0))
        else
                Format.printf "No card@."

let () =
        let numbers = List.init 100 (fun i -> i + 1) in
        List.iter deal_one_hand numbers;
