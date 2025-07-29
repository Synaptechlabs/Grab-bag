type expr =
  | Const of int
  | Var of string
  | Add of expr * expr
  | Sub of expr * expr
  | Mul of expr * expr

let rec to_string e =
  match e with
  | Const n -> string_of_int n
  | Var x -> x
  | Add (a, b) -> "(" ^ to_string a ^ " + " ^ to_string b ^ ")"
  | Sub (a, b) -> "(" ^ to_string a ^ " - " ^ to_string b ^ ")"
  | Mul (a, b) -> "(" ^ to_string a ^ " * " ^ to_string b ^ ")"

let () =
  let e = Add (Mul (Const 2, Var "x"), Mul (Const 3, Var "x")) in
  print_endline (to_string e)

