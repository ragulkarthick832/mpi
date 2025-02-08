main :: IO ()
main = do
    let result = foldr (:) [] [1,2,3,4]
    print result
