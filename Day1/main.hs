calcFuel :: Integer -> Integer
calcFuel mass | mass > 5  = mass `div` 3 - 2
              | otherwise = 0

calcTrickleFuel :: Integer -> Integer -> Integer
calcTrickleFuel acc 0    = acc
calcTrickleFuel acc mass = calcTrickleFuel (acc+reqFuel) reqFuel
                           where reqFuel = calcFuel mass

main :: IO ()
main = do
    masses <- readFile "input.txt"
    let parsedMasses = map read (lines masses) :: [Integer]
    let totalReqFuel = sum $ map (calcTrickleFuel 0) parsedMasses
    print totalReqFuel
