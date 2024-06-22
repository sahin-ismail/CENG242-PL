module HW2 (
    parse, -- reexport for easy terminal use
    foldAndPropagateConstants,
    assignCommonSubexprs,
    reducePoly
) where

import Expression
import Parser

-- Do not change the module definition and imports above! Feel free
-- to modify the parser, but please remember that it is just a helper
-- module and is not related to your grade. You should only submit
-- this file. Feel free to import other modules, especially Data.List!


-- Variables for *****foldAndPropagateConstants*****

templist :: [(String,Int)]
templist = []

-- Variables for *****assignCommonSubexprs*****

templs :: [(String, ExprV)]
templs = []



--------------------------------------------------------------------



foldAndPropagateConstants :: [(String, ExprV)] -> [(String, ExprV)]
foldAndPropagateConstants [] = []
foldAndPropagateConstants list = newParseFirst list templist


assignCommonSubexprs :: ExprV -> ([(String, ExprV)], ExprV)
assignCommonSubexprs a = assignHelper 0 a templs 
 
reducePoly :: ExprV -> ExprV
reducePoly a = reduceHelperFirst(a) 

-- an extra dummy variable, so as to not crash the GUI
notImpl :: ExprV
notImpl = Leaf $ Variable "Not Implemented"



--------------------------------------------------------------------



-- Helper Functions for *****foldAndPropagateConstants*****

isInList :: String -> [(String, Int)] -> (Int , Int)
isInList s [] = (0,0)
isInList s (y:ys) = if s == fst(y) then (1, snd(y)) else isInList s ys


getS :: ExprV -> String
getS (Leaf (Variable a)) = a

newParseFirst :: [(String, ExprV)] -> [(String, Int)] -> [(String, ExprV)]
newParseFirst [] templist = []
newParseFirst ((s,a):xs) templist = (fst(newParse((s , a), templist))) : (newParseFirst xs (snd(newParse((s , a), templist))))

getLeaf :: ExprV -> (Int,Int)
getLeaf (Leaf (Variable a)) = (0, 0)
getLeaf (Leaf (Constant a)) = (1, a)

doOp :: ExprV -> (((Int,Int),Int),ExprV)
doOp (BinaryOperation Plus left right) =  add left right
doOp (BinaryOperation Times left right) =  mult left right
 
add :: ExprV -> ExprV -> (((Int,Int),Int),ExprV)
add (Leaf (Constant a)) (Leaf (Constant b)) =  (((0,0),a+b),Leaf (Constant (a+b)))
add (BinaryOperation boperator left right) (BinaryOperation boperator1 left1 right1) = (((1,1),0), (BinaryOperation Plus (BinaryOperation boperator left right) (BinaryOperation boperator left1 right1) ))
add (BinaryOperation boperator left right) (Leaf (b)) = (((1,0),0),(BinaryOperation Plus (BinaryOperation boperator left right) (Leaf(b))))
add (Leaf (b)) (BinaryOperation boperator left right) = (((0,1),0),(BinaryOperation Plus (Leaf(b)) (BinaryOperation boperator left right)))
add (Leaf (Constant b)) (Leaf (Variable c))  = (((1,2),0),(BinaryOperation Plus (Leaf (Constant b)) (Leaf (Variable c)) ))
add (Leaf (Variable b)) (Leaf (Constant c))  = (((2,1),0),(BinaryOperation Plus (Leaf (Variable b)) (Leaf (Constant c)) ))
add (Leaf (Variable b)) (Leaf (Variable c))  = (((2,2),0),(BinaryOperation Plus (Leaf (Variable b)) (Leaf (Variable c)) ))


mult :: ExprV -> ExprV -> (((Int,Int),Int),ExprV)
mult (Leaf (Constant a)) (Leaf (Constant b)) =  (((0,0),a*b),Leaf (Constant (a*b)))
mult (BinaryOperation boperator left right) (BinaryOperation boperator1 left1 right1) = (((1,1),0), (BinaryOperation Times (BinaryOperation boperator left right) (BinaryOperation boperator left1 right1) ))
mult (BinaryOperation boperator left right) (Leaf (b)) = (((1,0),0),(BinaryOperation Times (BinaryOperation boperator left right) (Leaf(b))))
mult (Leaf (b)) (BinaryOperation boperator left right) = (((0,1),0),(BinaryOperation Times (Leaf(b)) (BinaryOperation boperator left right)))
mult (Leaf (Constant b)) (Leaf (Variable c))  = (((1,2),0),(BinaryOperation Times (Leaf (Constant b)) (Leaf (Variable c)) ))
mult (Leaf (Variable b)) (Leaf (Constant c))  = (((2,1),0),(BinaryOperation Times (Leaf (Variable b)) (Leaf (Constant c)) ))
mult (Leaf (Variable b)) (Leaf (Variable c))  = (((2,2),0),(BinaryOperation Times (Leaf (Variable b)) (Leaf (Variable c)) ))

isInt :: String -> ExprV -> [(String, Int)]
isInt s (Leaf (Constant x)) = [(s,x)]
isInt s _ = []

doMin :: ExprV -> [(String, Int)] -> ExprV
doMin (Leaf (Constant a)) list= (Leaf (Constant (-a)))
doMin a list = snd(fst(newParse(("-",a),list)))

newParse :: ((String, ExprV), [(String, Int)]) -> ((String, ExprV), [(String, Int)])
newParse ((s ,(Leaf a)),list) = if s == "-" then
                                    (if fst (getLeaf(Leaf a)) == 0 then 
                                        (if fst(isInList (getS (Leaf a)) list) == 0 then ((s,(Leaf a)),list)
                                        else ((s,(Leaf (Constant (snd(isInList (getS (Leaf a)) list))))),list))
                                    else ((s,(Leaf a)),(list)))
                                else
                                    (if fst (getLeaf(Leaf a)) == 0 then 
                                        (if fst(isInList (getS (Leaf a)) list) == 0 then ((s,(Leaf a)),list)
                                        else ((s,(Leaf (Constant (snd(isInList (getS (Leaf a)) list))))),((s, (snd(isInList (getS (Leaf a)) list))):list)))
                                    else ((s,(Leaf a)),((s, (snd (getLeaf(Leaf a)))):list)))
newParse ((s ,(BinaryOperation boperator left right)),list) = if s == "-" then
                                                                  (if (fst(fst(doOp (BinaryOperation boperator left right)))) == (0,0) then ((s,(snd(doOp (BinaryOperation boperator left right)))),list)
                                                                  else if (fst(fst(doOp (BinaryOperation boperator left right)))) == (1,1) then ((s,(snd(doOp (BinaryOperation boperator (snd(fst(newParse (("-",left),list)))) (snd(fst(newParse (("-",right),list)))) )))),list)
                                                                  else if (fst(fst(doOp (BinaryOperation boperator left right)))) == (1,0) then ((s,(snd(doOp (BinaryOperation boperator (snd(fst(newParse (("-",left),list)))) (snd(fst(newParse (("-",right),list)))) )))),list)
                                                                  else if (fst(fst(doOp (BinaryOperation boperator left right)))) == (0,1) then ((s,(snd(doOp (BinaryOperation boperator (snd(fst(newParse (("-",left),list)))) (snd(fst(newParse (("-",right),list)))) )))),list)
                                                                  else if (fst(fst(doOp (BinaryOperation boperator left right)))) == (1,2) then ((s,(snd(doOp (BinaryOperation boperator left (snd(fst(newParse (("-",right),list)))) )))),list)
                                                                  else if (fst(fst(doOp (BinaryOperation boperator left right)))) == (2,1) then ((s,(snd(doOp (BinaryOperation boperator (snd(fst(newParse (("-",left),list)))) right )))),list)
                                                                  else if (fst(fst(doOp (BinaryOperation boperator left right)))) == (2,2) then ((s,(snd(doOp (BinaryOperation boperator (snd(fst(newParse (("-",left),list)))) (snd(fst(newParse (("-",right),list)))) )))),list)
                                                                  else (("x",(Leaf (Constant 5))),list))
                                                              else
                                                                  (if (fst(fst(doOp (BinaryOperation boperator left right)))) == (0,0) then ((s,(snd(doOp (BinaryOperation boperator left right)))),(isInt s (snd(doOp (BinaryOperation boperator left right))))++list)
                                                                  else if (fst(fst(doOp (BinaryOperation boperator left right)))) == (1,1) then ((s,(snd(doOp (BinaryOperation boperator (snd(fst(newParse (("-",left),list)))) (snd(fst(newParse (("-",right),list)))) )))),(isInt s (snd(doOp (BinaryOperation boperator (snd(fst(newParse (("-",left),list)))) (snd(fst(newParse (("-",right),list)))) ))))++list)
                                                                  else if (fst(fst(doOp (BinaryOperation boperator left right)))) == (1,0) then ((s,(snd(doOp (BinaryOperation boperator (snd(fst(newParse (("-",left),list)))) (snd(fst(newParse (("-",right),list)))) )))),(isInt s (snd(doOp (BinaryOperation boperator (snd(fst(newParse (("-",left),list)))) (snd(fst(newParse (("-",right),list)))) ))))++list)
                                                                  else if (fst(fst(doOp (BinaryOperation boperator left right)))) == (0,1) then ((s,(snd(doOp (BinaryOperation boperator (snd(fst(newParse (("-",left),list)))) (snd(fst(newParse (("-",right),list)))) )))),(isInt s (snd(doOp (BinaryOperation boperator (snd(fst(newParse (("-",left),list)))) (snd(fst(newParse (("-",right),list)))) ))))++list)
                                                                  else if (fst(fst(doOp (BinaryOperation boperator left right)))) == (1,2) then ((s,(snd(doOp (BinaryOperation boperator left (snd(fst(newParse (("-",right),list)))) )))),(isInt s (snd(doOp (BinaryOperation boperator left (snd(fst(newParse (("-",right),list)))) ))))++list)
                                                                  else if (fst(fst(doOp (BinaryOperation boperator left right)))) == (2,1) then ((s,(snd(doOp (BinaryOperation boperator (snd(fst(newParse (("-",left),list)))) right )))),(isInt s (snd(doOp (BinaryOperation boperator (snd(fst(newParse (("-",left),list)))) right ))))++list)
                                                                  else if (fst(fst(doOp (BinaryOperation boperator left right)))) == (2,2) then ((s,(snd(doOp (BinaryOperation boperator (snd(fst(newParse (("-",left),list)))) (snd(fst(newParse (("-",right),list)))) )))),(isInt s (snd(doOp (BinaryOperation boperator (snd(fst(newParse (("-",left),list)))) (snd(fst(newParse (("-",right),list)))) ))))++list)
                                                                  else (("x",(Leaf (Constant 5))),list))
newParse ((s ,(UnaryOperation uoperator only)),list) = ((s,(doMin only list)),list)


-- Helper Functions for *****assignCommonSubexprs*****

assignHelper:: Int -> ExprV -> [(String, ExprV)] -> ([(String, ExprV)], ExprV)
assignHelper 0 (UnaryOperation uoperator (Leaf a)) list = (list,(UnaryOperation uoperator (Leaf a)))
assignHelper 0 (UnaryOperation uoperator (BinaryOperation boperator left right)) list = ( (fst(assignHelper 1 (BinaryOperation boperator left right) list)),(UnaryOperation uoperator (snd(assignHelper 1 (BinaryOperation boperator left right) list)) ))

assignHelper 0 (BinaryOperation boperator0 (UnaryOperation uoperator only) (UnaryOperation uoperator1 only1)) list = ((fst(assignHelper 1 (UnaryOperation uoperator1 only1) (fst(assignHelper 1 (UnaryOperation uoperator only) list)) )),(BinaryOperation boperator0 (snd(assignHelper 1 (UnaryOperation uoperator only) list)) (snd(assignHelper 1 (UnaryOperation uoperator1 only1) (fst(assignHelper 1 (UnaryOperation uoperator only) list)) )) ))
assignHelper 0 (BinaryOperation boperator0 (UnaryOperation uoperator only) (Leaf a)) list = ((fst(assignHelper 1 (UnaryOperation uoperator only) list)),(BinaryOperation boperator0 (snd(assignHelper 1 (UnaryOperation uoperator only) list)) (Leaf a) ))
assignHelper 0 (BinaryOperation boperator0 (Leaf a) (UnaryOperation uoperator only)) list = ((fst(assignHelper 1 (UnaryOperation uoperator only) list)),(BinaryOperation boperator0 (Leaf a) (snd(assignHelper 1 (UnaryOperation uoperator only) list)) ))
assignHelper 0 (BinaryOperation boperator0 (UnaryOperation uoperator only) (BinaryOperation boperator left right)) list = ((fst(assignHelper 1 (BinaryOperation boperator left right) (fst(assignHelper 1 (UnaryOperation uoperator only) list)) )),(BinaryOperation boperator0 (snd(assignHelper 1 (UnaryOperation uoperator only) list)) (snd(assignHelper 1 (BinaryOperation boperator left right) (fst(assignHelper 1 (UnaryOperation uoperator only) list)) )) ))
assignHelper 0 (BinaryOperation boperator0 (BinaryOperation boperator left right) (UnaryOperation uoperator1 only1)) list = ((fst(assignHelper 1 (UnaryOperation uoperator1 only1) (fst(assignHelper 1 (BinaryOperation boperator left right) list)) )),(BinaryOperation boperator0 (snd(assignHelper 1 (BinaryOperation boperator left right) list)) (snd(assignHelper 1 (UnaryOperation uoperator1 only1) (fst(assignHelper 1 (BinaryOperation boperator left right) list)) )) ))

assignHelper 0 (BinaryOperation boperator0 (Leaf a) (Leaf b)) list = (list,(BinaryOperation boperator0 (Leaf a) (Leaf b)))
assignHelper 0 (BinaryOperation boperator0 (BinaryOperation boperator left right) (BinaryOperation boperator1 left1 right1)) list = ((fst(assignHelper 1 (BinaryOperation boperator1 left1 right1) (fst(assignHelper 1 (BinaryOperation boperator left right) list)) )),(BinaryOperation boperator0 (snd(assignHelper 1 (BinaryOperation boperator left right) list)) (snd(assignHelper 1 (BinaryOperation boperator1 left1 right1) (fst(assignHelper 1 (BinaryOperation boperator left right) list)) )) ))
assignHelper 0 (BinaryOperation boperator0 (BinaryOperation boperator left right) (Leaf a)) list = ((fst(assignHelper 1 (BinaryOperation boperator left right) list)),(BinaryOperation boperator0 (snd(assignHelper 1 (BinaryOperation boperator left right) list)) (Leaf a) ))
assignHelper 0 (BinaryOperation boperator0 (Leaf a) (BinaryOperation boperator left right)) list = ((fst(assignHelper 1 (BinaryOperation boperator left right) list)),(BinaryOperation boperator0 (Leaf a) (snd(assignHelper 1 (BinaryOperation boperator left right) list)) ))


assignHelper 1 (UnaryOperation uoperator (Leaf a)) list = if fst(assignIsInList (UnaryOperation uoperator (Leaf a) ) list) == 0 then
                                                              ((list++[(("$"++show (length list)), (UnaryOperation uoperator (Leaf a) ))]), (Leaf (Variable ("$"++show (length list)))))
                                                          else 
                                                              (list,(Leaf (Variable (snd(assignIsInList (UnaryOperation uoperator (Leaf a) ) list)))))
assignHelper 1 (UnaryOperation uoperator (BinaryOperation boperator left right)) list = if fst(assignIsInList (UnaryOperation uoperator (snd(assignHelper 1 (BinaryOperation boperator left right) list)) ) list) == 0 then
                                                                                            (((fst(assignHelper 1 (BinaryOperation boperator left right) list))++[(("$"++show (length (fst(assignHelper 1 (BinaryOperation boperator left right) list)))), (UnaryOperation uoperator (snd(assignHelper 1 (BinaryOperation boperator left right) list)) ))]), (Leaf (Variable ("$"++show (length (fst(assignHelper 1 (BinaryOperation boperator left right) list)))))))
                                                                                        else 
                                                                                            (list,(Leaf (Variable (snd(assignIsInList (UnaryOperation uoperator (snd(assignHelper 1 (BinaryOperation boperator left right) list)) ) list)))))




assignHelper 1 (BinaryOperation boperator0 (UnaryOperation uoperator only) (UnaryOperation uoperator1 only1)) list =  if (snd(assignIsInList ( (snd(assignHelper 1 (UnaryOperation uoperator only) list)) ) (fst(assignHelper 1 (UnaryOperation uoperator only) list)))) == (snd(assignIsInList ((snd(assignHelper 1 (UnaryOperation uoperator1 only1) (fst(assignHelper 1 (UnaryOperation uoperator only) list)) )) ) (fst(assignHelper 1 (UnaryOperation uoperator1 only1) (fst(assignHelper 1 (UnaryOperation uoperator only) list)) ))))  then
                                                                                                                            ((fst(assignHelper 1 (UnaryOperation uoperator only) list)),(BinaryOperation boperator0 (snd(assignHelper 1 (UnaryOperation uoperator only) list)) (snd(assignHelper 1 (UnaryOperation uoperator1 only1) (fst(assignHelper 1 (UnaryOperation uoperator only) list)))) ))
                                                                                                                                    
                                                                                                                      else if (fst(assignIsInList (BinaryOperation boperator0 (UnaryOperation uoperator only) (UnaryOperation uoperator1 only1)) list))+(fst(assignIsInList (BinaryOperation boperator0 (snd(assignHelper 1 (UnaryOperation uoperator only) list)) (snd(assignHelper 1 (UnaryOperation uoperator1 only1) (fst(assignHelper 1 (UnaryOperation uoperator only) list)) )) ) list)) == 0 then
                                                                                                                            ((fst(assignHelper 1 (UnaryOperation uoperator1 only1) (fst(assignHelper 1 (UnaryOperation uoperator only) list)) ))++[(("$"++show (length (fst(assignHelper 1 (UnaryOperation uoperator1 only1) (fst(assignHelper 1 (UnaryOperation uoperator only) list)) )))), (BinaryOperation boperator0 (snd(assignHelper 1 (UnaryOperation uoperator only) list)) (snd(assignHelper 1 (UnaryOperation uoperator1 only1) (fst(assignHelper 1 (UnaryOperation uoperator only) list)) )) ))] , (Leaf (Variable ("$"++show (length (fst(assignHelper 1 (UnaryOperation uoperator1 only1) (fst(assignHelper 1 (UnaryOperation uoperator only) list)) )))))) )
                                                                                                                      else
                                                                                                                            (if (fst(assignIsInList (BinaryOperation boperator0 (UnaryOperation uoperator only) (UnaryOperation uoperator1 only1)) list)) == 1 then
                                                                                                                                    (list,(Leaf (Variable (snd(assignIsInList (BinaryOperation boperator0 (UnaryOperation uoperator only) (UnaryOperation uoperator1 only1)) list)))))
                                                                                                                             else (list,(Leaf (Variable (snd(assignIsInList (BinaryOperation boperator0 (snd(assignHelper 1 (UnaryOperation uoperator only) list)) (snd(assignHelper 1 (UnaryOperation uoperator1 only1) (fst(assignHelper 1 (UnaryOperation uoperator only) list)) )) ) list))))))
assignHelper 1 (BinaryOperation boperator0 (UnaryOperation uoperator only) (Leaf a)) list = if (fst(assignIsInList (BinaryOperation boperator0 (UnaryOperation uoperator only) (Leaf a)) list))+(fst(assignIsInList (BinaryOperation boperator0 (snd(assignHelper 1 (UnaryOperation uoperator only) list)) (Leaf a)) list)) == 0 then
                                                                                                ((fst(assignHelper 1 (UnaryOperation uoperator only) list))++[(("$"++show (length (fst(assignHelper 1 (UnaryOperation uoperator only) list)))), (BinaryOperation boperator0 (snd(assignHelper 1 (UnaryOperation uoperator only) list)) (Leaf a)))], (Leaf (Variable ("$"++show (length (fst(assignHelper 1 (UnaryOperation uoperator only) list)))))))
                                                                                            else
                                                                                                (if (fst(assignIsInList (BinaryOperation boperator0 (UnaryOperation uoperator only) (Leaf a)) list)) == 1 then
                                                                                                    (list,(Leaf (Variable (snd(assignIsInList (BinaryOperation boperator0 (UnaryOperation uoperator only) (Leaf a)) list)))))
                                                                                                else
                                                                                                           (list,(Leaf (Variable (snd(assignIsInList (BinaryOperation boperator0 (snd(assignHelper 1 (UnaryOperation uoperator only) list)) (Leaf a)) list)))))) 
assignHelper 1 (BinaryOperation boperator0 (Leaf a) (UnaryOperation uoperator only)) list = if (fst(assignIsInList (BinaryOperation boperator0 (Leaf a) (UnaryOperation uoperator only)) list))+(fst(assignIsInList (BinaryOperation boperator0 (Leaf a) (snd(assignHelper 1 (UnaryOperation uoperator only) list))) list)) == 0 then
                                                                                                ((fst(assignHelper 1 (UnaryOperation uoperator only) list))++[(("$"++show (length (fst(assignHelper 1 (UnaryOperation uoperator only) list)))), (BinaryOperation boperator0 (Leaf a) (snd(assignHelper 1 (UnaryOperation uoperator only) list))))], (Leaf (Variable ("$"++show (length (fst(assignHelper 1 (UnaryOperation uoperator only) list)))))))
                                                                                            else 
                                                                                                (if (fst(assignIsInList (BinaryOperation boperator0 (Leaf a) (UnaryOperation uoperator only)) list)) == 1 then
                                                                                                    (list,(Leaf (Variable (snd(assignIsInList (BinaryOperation boperator0 (Leaf a) (UnaryOperation uoperator only)) list)))))
                                                                                                else
                                                                                                    (list,(Leaf (Variable (snd(assignIsInList (BinaryOperation boperator0 (Leaf a) (snd(assignHelper 1 (UnaryOperation uoperator only) list))) list))))))
assignHelper 1 (BinaryOperation boperator0 (UnaryOperation uoperator only) (BinaryOperation boperator1 left1 right1)) list = if (snd(assignIsInList ( (snd(assignHelper 1 (UnaryOperation uoperator only) list)) ) (fst(assignHelper 1 (UnaryOperation uoperator only) list)))) == (snd(assignIsInList ((snd(assignHelper 1 (BinaryOperation boperator1 left1 right1) (fst(assignHelper 1 (UnaryOperation uoperator only) list)) )) ) (fst(assignHelper 1 (BinaryOperation boperator1 left1 right1) (fst(assignHelper 1 (UnaryOperation uoperator only) list)) ))))  then
                                                                                                                                ((fst(assignHelper 1 (UnaryOperation uoperator only) list)),(BinaryOperation boperator0 (snd(assignHelper 1 (UnaryOperation uoperator only) list)) (snd(assignHelper 1 (BinaryOperation boperator1 left1 right1) (fst(assignHelper 1 (UnaryOperation uoperator only) list)))) ))
                                                                                                                                    
                                                                                                                            else if (fst(assignIsInList (BinaryOperation boperator0 (UnaryOperation uoperator only) (BinaryOperation boperator1 left1 right1)) list))+(fst(assignIsInList (BinaryOperation boperator0 (snd(assignHelper 1 (UnaryOperation uoperator only) list)) (snd(assignHelper 1 (BinaryOperation boperator1 left1 right1) (fst(assignHelper 1 (UnaryOperation uoperator only) list)) )) ) list)) == 0 then
                                                                                                                                        ((fst(assignHelper 1 (BinaryOperation boperator1 left1 right1) (fst(assignHelper 1 (UnaryOperation uoperator only) list)) ))++[(("$"++show (length (fst(assignHelper 1 (BinaryOperation boperator1 left1 right1) (fst(assignHelper 1 (UnaryOperation uoperator only) list)) )))), (BinaryOperation boperator0 (snd(assignHelper 1 (UnaryOperation uoperator only) list)) (snd(assignHelper 1 (BinaryOperation boperator1 left1 right1) (fst(assignHelper 1 (UnaryOperation uoperator only) list)) )) ))] , (Leaf (Variable ("$"++show (length (fst(assignHelper 1 (BinaryOperation boperator1 left1 right1) (fst(assignHelper 1 (UnaryOperation uoperator only) list)) )))))) )
                                                                                                                            else
                                                                                                                                (if (fst(assignIsInList (BinaryOperation boperator0 (UnaryOperation uoperator only) (BinaryOperation boperator1 left1 right1)) list)) == 1 then
                                                                                                                                    (list,(Leaf (Variable (snd(assignIsInList (BinaryOperation boperator0 (UnaryOperation uoperator only) (BinaryOperation boperator1 left1 right1)) list)))))
                                                                                                                                 else (list,(Leaf (Variable (snd(assignIsInList (BinaryOperation boperator0 (snd(assignHelper 1 (UnaryOperation uoperator only) list)) (snd(assignHelper 1 (BinaryOperation boperator1 left1 right1) (fst(assignHelper 1 (UnaryOperation uoperator only) list)) )) ) list))))))
assignHelper 1 (BinaryOperation boperator0 (BinaryOperation boperator left right) (UnaryOperation uoperator only)) list = if (snd(assignIsInList ( (snd(assignHelper 1 (BinaryOperation boperator left right) list)) ) (fst(assignHelper 1 (BinaryOperation boperator left right) list)))) == (snd(assignIsInList ((snd(assignHelper 1 (UnaryOperation uoperator only) (fst(assignHelper 1 (BinaryOperation boperator left right) list)) )) ) (fst(assignHelper 1 (UnaryOperation uoperator only) (fst(assignHelper 1 (BinaryOperation boperator left right) list)) ))))  then
                                                                                                                                ((fst(assignHelper 1 (BinaryOperation boperator left right) list)),(BinaryOperation boperator0 (snd(assignHelper 1 (BinaryOperation boperator left right) list)) (snd(assignHelper 1 (UnaryOperation uoperator only) (fst(assignHelper 1 (BinaryOperation boperator left right) list)))) ))
                                                                                                                                    
                                                                                                                            else if (fst(assignIsInList (BinaryOperation boperator0 (BinaryOperation boperator left right) (UnaryOperation uoperator only)) list))+(fst(assignIsInList (BinaryOperation boperator0 (snd(assignHelper 1 (BinaryOperation boperator left right) list)) (snd(assignHelper 1 (UnaryOperation uoperator only) (fst(assignHelper 1 (BinaryOperation boperator left right) list)) )) ) list)) == 0 then
                                                                                                                                ((fst(assignHelper 1 (UnaryOperation uoperator only) (fst(assignHelper 1 (BinaryOperation boperator left right) list)) ))++[(("$"++show (length (fst(assignHelper 1 (UnaryOperation uoperator only) (fst(assignHelper 1 (BinaryOperation boperator left right) list)) )))), (BinaryOperation boperator0 (snd(assignHelper 1 (BinaryOperation boperator left right) list)) (snd(assignHelper 1 (UnaryOperation uoperator only) (fst(assignHelper 1 (BinaryOperation boperator left right) list)) )) ))] , (Leaf (Variable ("$"++show (length (fst(assignHelper 1 (UnaryOperation uoperator only) (fst(assignHelper 1 (BinaryOperation boperator left right) list)) )))))) )
                                                                                                                            else
                                                                                                                                (if (fst(assignIsInList (BinaryOperation boperator0 (BinaryOperation boperator left right) (UnaryOperation uoperator only)) list)) == 1 then
                                                                                                                                            (list,(Leaf (Variable (snd(assignIsInList (BinaryOperation boperator0 (BinaryOperation boperator left right) (UnaryOperation uoperator only)) list)))))
                                                                                                                                else (list,(Leaf (Variable (snd(assignIsInList (BinaryOperation boperator0 (snd(assignHelper 1 (BinaryOperation boperator left right) list)) (snd(assignHelper 1 (UnaryOperation uoperator only) (fst(assignHelper 1 (BinaryOperation boperator left right) list)) )) ) list))))))





assignHelper 1 (BinaryOperation boperator0 (Leaf a) (Leaf b)) list = if fst(assignIsInList (BinaryOperation boperator0 (Leaf a) (Leaf b)) list) == 0 then
                                                                         ((list ++ [(("$"++show (length list)), (BinaryOperation boperator0 (Leaf a) (Leaf b)))]), (Leaf (Variable ("$"++show (length list) ))))
                                                                     else 
                                                                         (list,(Leaf (Variable (snd(assignIsInList (BinaryOperation boperator0 (Leaf a) (Leaf b)) list)))))
assignHelper 1 (BinaryOperation boperator0 (BinaryOperation boperator left right) (BinaryOperation boperator1 left1 right1)) list = if (snd(assignIsInList ( (snd(assignHelper 1 (BinaryOperation boperator left right) list)) ) (fst(assignHelper 1 (BinaryOperation boperator left right) list)))) == (snd(assignIsInList ((snd(assignHelper 1 (BinaryOperation boperator1 left1 right1) (fst(assignHelper 1 (BinaryOperation boperator left right) list)) )) ) (fst(assignHelper 1 (BinaryOperation boperator1 left1 right1) (fst(assignHelper 1 (BinaryOperation boperator left right) list)) ))))  then
                                                                                                                                        ((fst(assignHelper 1 (BinaryOperation boperator left right) list)),(BinaryOperation boperator0 (snd(assignHelper 1 (BinaryOperation boperator left right) list)) (snd(assignHelper 1 (BinaryOperation boperator1 left1 right1) (fst(assignHelper 1 (BinaryOperation boperator left right) list)))) ))
                                                                                                                                    
                                                                                                                                    else if (fst(assignIsInList (BinaryOperation boperator0 (BinaryOperation boperator left right) (BinaryOperation boperator1 left1 right1)) list))+(fst(assignIsInList (BinaryOperation boperator0 (snd(assignHelper 1 (BinaryOperation boperator left right) list)) (snd(assignHelper 1 (BinaryOperation boperator1 left1 right1) (fst(assignHelper 1 (BinaryOperation boperator left right) list)) )) ) list)) == 0 then
                                                                                                                                        ((fst(assignHelper 1 (BinaryOperation boperator1 left1 right1) (fst(assignHelper 1 (BinaryOperation boperator left right) list)) ))++[(("$"++show (length (fst(assignHelper 1 (BinaryOperation boperator1 left1 right1) (fst(assignHelper 1 (BinaryOperation boperator left right) list)) )))), (BinaryOperation boperator0 (snd(assignHelper 1 (BinaryOperation boperator left right) list)) (snd(assignHelper 1 (BinaryOperation boperator1 left1 right1) (fst(assignHelper 1 (BinaryOperation boperator left right) list)) )) ))] , (Leaf (Variable ("$"++show (length (fst(assignHelper 1 (BinaryOperation boperator1 left1 right1) (fst(assignHelper 1 (BinaryOperation boperator left right) list)) )))))) )
                                                                                                                                    else
                                                                                                                                        (if (fst(assignIsInList (BinaryOperation boperator0 (BinaryOperation boperator left right) (BinaryOperation boperator1 left1 right1)) list)) == 1 then
                                                                                                                                            (list,(Leaf (Variable (snd(assignIsInList (BinaryOperation boperator0 (BinaryOperation boperator left right) (BinaryOperation boperator1 left1 right1)) list)))))
                                                                                                                                        else (list,(Leaf (Variable (snd(assignIsInList (BinaryOperation boperator0 (snd(assignHelper 1 (BinaryOperation boperator left right) list)) (snd(assignHelper 1 (BinaryOperation boperator1 left1 right1) (fst(assignHelper 1 (BinaryOperation boperator left right) list)) )) ) list))))))
assignHelper 1 (BinaryOperation boperator0 (BinaryOperation boperator left right) (Leaf a)) list = if (fst(assignIsInList (BinaryOperation boperator0 (BinaryOperation boperator left right) (Leaf a)) list))+(fst(assignIsInList (BinaryOperation boperator0 (snd(assignHelper 1 (BinaryOperation boperator left right) list)) (Leaf a)) list)) == 0 then
                                                                                                       ((fst(assignHelper 1 (BinaryOperation boperator left right) list))++[(("$"++show (length (fst(assignHelper 1 (BinaryOperation boperator left right) list)))), (BinaryOperation boperator0 (snd(assignHelper 1 (BinaryOperation boperator left right) list)) (Leaf a)))], (Leaf (Variable ("$"++show (length (fst(assignHelper 1 (BinaryOperation boperator left right) list)))))))
                                                                                                   else
                                                                                                       (if (fst(assignIsInList (BinaryOperation boperator0 (BinaryOperation boperator left right) (Leaf a)) list)) == 1 then
                                                                                                           (list,(Leaf (Variable (snd(assignIsInList (BinaryOperation boperator0 (BinaryOperation boperator left right) (Leaf a)) list)))))
                                                                                                        else
                                                                                                           (list,(Leaf (Variable (snd(assignIsInList (BinaryOperation boperator0 (snd(assignHelper 1 (BinaryOperation boperator left right) list)) (Leaf a)) list)))))) 
assignHelper 1 (BinaryOperation boperator0 (Leaf a) (BinaryOperation boperator left right)) list = if (fst(assignIsInList (BinaryOperation boperator0 (Leaf a) (BinaryOperation boperator left right)) list))+(fst(assignIsInList (BinaryOperation boperator0 (Leaf a) (snd(assignHelper 1 (BinaryOperation boperator left right) list))) list)) == 0 then
                                                                                                       ((fst(assignHelper 1 (BinaryOperation boperator left right) list))++[(("$"++show (length (fst(assignHelper 1 (BinaryOperation boperator left right) list)))), (BinaryOperation boperator0 (Leaf a) (snd(assignHelper 1 (BinaryOperation boperator left right) list))))], (Leaf (Variable ("$"++show (length (fst(assignHelper 1 (BinaryOperation boperator left right) list)))))))
                                                                                                   else 
                                                                                                       (if (fst(assignIsInList (BinaryOperation boperator0 (Leaf a) (BinaryOperation boperator left right)) list)) == 1 then
                                                                                                           (list,(Leaf (Variable (snd(assignIsInList (BinaryOperation boperator0 (Leaf a) (BinaryOperation boperator left right)) list)))))
                                                                                                        else
                                                                                                           (list,(Leaf (Variable (snd(assignIsInList (BinaryOperation boperator0 (Leaf a) (snd(assignHelper 1 (BinaryOperation boperator left right) list))) list))))))





assignIsInList:: ExprV -> [(String, ExprV)] -> (Int, String)
assignIsInList a [] = (0,"--")
assignIsInList a (list:ls) = if a == snd(list) then (1,fst(list)) else assignIsInList a ls







-- Helper Functions for *****reducePoly*****
reduceHelperFirst:: ExprV -> ExprV
reduceHelperFirst a = parse ((toStr a (reduceHelper a) 0)) --reduceHelper(a)


reduceHelper:: ExprV -> [Int]
reduceHelper (Leaf (Variable a)) = [0,1]
reduceHelper (Leaf (Constant a)) = [a]
reduceHelper (BinaryOperation Times left right) = multLists (reduceHelper left) (reduceHelper right)
reduceHelper (BinaryOperation Plus left right) = addLists (reduceHelper left) (reduceHelper right)
reduceHelper (UnaryOperation Minus (Leaf (Variable a))) = [0,-1]
reduceHelper (UnaryOperation Minus (Leaf (Constant a))) = [-a]


multLists:: [Int] -> [Int] -> [Int]
multLists x y = addAllList(addZeros ([ map (a*) y | a <-x]) 0 ((length [ map (a*) y | a <-x])-1))


addLists:: [Int] -> [Int] -> [Int]
addLists x y = if (length x) == (length y) then zipWith (+) x y
               else if (length x) > (length y) then (zipWith (+) x y)++(drop (length y) x)
               else (zipWith (+) x y)++(drop (length x) y)


addZeros:: [[Int]] -> Int -> Int -> [[Int]]
addZeros [] _ _ = []
addZeros (l:list) a len = ((addZeroHelp a)++l++(addZeroHelp (len-a))):(addZeros list (a+1) len) --length-1 ile çağır


addZeroHelp:: Int -> [Int]
addZeroHelp 0 = []
addZeroHelp a = 0:(addZeroHelp (a-1))


addAllList:: [[Int]] -> [Int]
addAllList [] = []
addAllList (l:list) = addLists l (addAllList list)


getVarFirst:: ExprV -> String
getVarFirst a = if (getVar a) == [] then "--"
                else (head (getVar a))


getVar:: ExprV -> [String]
getVar (Leaf (Variable x)) = x:[]
getVar (Leaf (Constant a)) = []
getVar (BinaryOperation boperator left right) = (getVar left)++(getVar right) 
getVar (UnaryOperation uoperator only) = (getVar only)

toStr:: ExprV -> [Int] -> Int -> String
toStr e [] _ = []
toStr e (l:list) a = "("++(if (a > 0) && (l==1) then [] else show (l))++(if (a > 0) && (l==1) then (dropOne (addVar e a)) else addVar e a)++")"++(if (toStr e list (a+1)) == [] then [] else "+"++(toStr e list (a+1)))

addVar:: ExprV -> Int -> String
addVar e 0 = []
addVar e a = ("*"++(getVarFirst e))++(addVar  e (a-1))

dropOne:: String -> String
dropOne [] = []
dropOne (s:st) = st