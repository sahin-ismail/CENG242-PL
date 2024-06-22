module HW1 (
    form,
    constGrid,
    flatten,
    access,
    slice,
    vcat,
    hcat,
    without,
    matches2d
) where

-- do not modify the module declaration above!
-- this will ensure that you cannot load (compile)
-- the module without implementing all of the functions.

-- If you have functions you do not want to implement,
-- leave them as undefined or make them have another
-- default value. If you fully remove any of their definitions,
-- that will be a compilation error during evaluation,
-- and you will be eligible for (yay!) a 5 point deduction
-- (that's bad for your grade). Runtime errors in your code 
-- (rather than compilation errors) are acceptable and will simply
-- result in you getting zero from the specific test case causing
-- an error.

-------------------------
-- Fellowship of the Grid (25, 5, 5, 5 points)
form :: [a] -> (Int, Int) -> [[a]] 
form [] (q,w) = []
form list (q,w) = [take w list] ++ (form (drop w list) (q,w))

constGrid :: a -> (Int, Int) -> [[a]]
constGrid val (0,w) = []
constGrid val (q,w) = take w (repeat val):(constGrid val (q-1,w))

flatten :: [[a]] -> [a]
flatten [] =  [] 
flatten (x:y) =  x ++ flatten y 

access :: [[a]] -> (Int, Int) -> a
access list (x,y) = (list!!x)!!y 
----------------------------
-- The Two Signatures (10, 5, 5, 10 points)
slice :: [[a]] -> (Int, Int) -> (Int, Int) -> [[a]]
slice list (i,r1) (j,r2) = [drop j(take (r2) l)|l<-(drop i (take (r1) list))]  

vcat :: [[a]] -> [[a]] -> [[a]]
vcat list1 list2 = list1 ++ list2

hcat :: [[a]] -> [[a]] -> [[a]]
hcat [] [] = []
hcat (q:r) (x:y) = [q ++ x] ++ hcat r y

without :: [[a]] -> (Int, Int) -> (Int, Int) -> [[a]]
without list (i,r1) (j,r2) = [((take j l)++(drop r2 l))|l<-((take i list)++(drop r1 list))]
----------------------------

-- Return of the Non-trivial (30 points, 15 subject to runtime constraints)
matches2d :: Eq a => [[a]] -> [[a]] -> [(Int, Int)]
matches2d list1 list2 = matches (length list1) (length (list1!!0)) (length list2) (length (list2!!0)) 0 0 0 0 list1 list2

-- matches :: Eq a => Int -> Int -> Int -> Int -> Int -> Int -> [[a]] -> [[a]] -> [(Int, Int)]
matches lengr lengc lenr lenc i j k l list1 list2 = if (slice list1 (j,lenr+k) (i,lenc+l)) == list2 
                                                    then [(j,i)] ++ if (i+lenc < length (list1!!0)) 
                                                                    then matches lengr lengc lenr lenc (i+1) j k (l+1) list1 list2 
                                                                    else if (j+lenr < length list1) 
                                                                         then matches lengr lengc lenr lenc (i-((length (list1!!0))-lenc)) (j+1) (k+1) 0  list1 list2 
                                                                         else [] 
                                                    else if (i+lenc < length (list1!!0)) 
                                                                    then matches lengr lengc lenr lenc (i+1) j k (l+1) list1 list2 
                                                                    else if (j+lenr < length list1) 
                                                                         then matches lengr lengc lenr lenc (i-((length (list1!!0))-lenc)) (j+1) (k+1) 0 list1 list2 
                                                                         else []
----------------------------
-- What is undefined? Just a value that will cause an error
-- when evaluated, from the GHC implementation:
-- undefined = error "Prelude.undefined"
-- But it allows your module to be compiled
-- since the function definitions will exist.
