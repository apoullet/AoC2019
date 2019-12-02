import Data.List
import Data.List.Split
import Data.Maybe

run :: [Int] -> Int -> [Int]
run program head | program !! head == 1 = run ((take pos program) ++ [valAtNoun + valAtVerb] ++ (drop (pos+1) program)) (head+4)
                 | program !! head == 2 = run ((take pos program) ++ [valAtNoun * valAtVerb] ++ (drop (pos+1) program)) (head+4)
                 | otherwise            = program
                   where noun      = program !! (head+1)
                         verb      = program !! (head+2)
                         pos       = program !! (head+3)
                         valAtNoun = program !! noun
                         valAtVerb = program !! verb

updateProgram :: [Int] -> Int -> Int -> [Int]
updateProgram program noun verb = (take 1 program) ++ [noun, verb] ++ (drop 3 program)

main :: IO ()
main = do
    program <- readFile "input_mod.txt"
    let parsedProgram = map read (splitOn "," program) :: [Int]
    let results = [[(run (updateProgram parsedProgram noun verb) 0) !! 0, noun, verb] | noun <- [0..100], verb <- [0..100]]
    let match = fromJust $ find (\e -> (e !! 0) == 19690720) results
    print $ 100 * (match !! 1) + (match !! 2)
