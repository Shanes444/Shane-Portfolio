import java.util.ArrayList;
import java.util.Collections;

public class convertNFA {
    public static DFA convertNFAtoDFA(NFA nfa){
        ArrayList<ArrayList<Integer>> states = new ArrayList<>(); //Empty array list that will have the new states
        states.add(nfa.lambdaClosure(nfa.initial)); //gets the lamda closure of the initial state and adds it to state 0 of the arraylist
        char[] sigma = nfa.sigma; // Gets the sigma so it can check all for each state
        boolean isNewState; // To track if the state is already added to the states list
        ArrayList<ArrayList<Integer>> transition = new ArrayList<>();
        ArrayList<Boolean> isAccepted = new ArrayList<>();
        isAccepted.add(nfa.accept(states.get(0)));
        int numStates = states.size();
        int i = 0;
        while(i < numStates){ //Iterates through all states
            transition.add(new ArrayList<>());
            for(int j = 0; j < sigma.length; j++){ //Iterates through sigma
                ArrayList<Integer> curCharLocations = nfa.whereCanGo(states.get(i), sigma[j]); //Checks where state can go with sigma input
                isNewState = true; //resets new state value
                Collections.sort(curCharLocations);
                for(int k = 0; k < states.size(); k++){ // checks if new state is in the array list already
                    if(arrayListEqual(states.get(k), curCharLocations)){
                        isNewState = false;
                        transition.get(i).add(k);
                        break;
                    }
                }
                if(isNewState){ // If the state is new it will be added to the list
                    states.add(curCharLocations);
                    isAccepted.add(nfa.accept(states.get(numStates)));
                    transition.get(i).add(numStates);
                    numStates++;
                }
            }
            i++;
        }
        // i = 0;
        // for(ArrayList<Integer> lst : states){
        //     System.out.print(i + ": ");
        //     for(Integer inte : lst){
        //         System.out.print(inte + " ");
        //     }
        //     System.out.println();
        //     i++;
        // }

        return new DFA(states, transition, sigma, isAccepted);
    }

    public static boolean arrayListEqual(ArrayList<Integer> arrLst1, ArrayList<Integer> arrLst2){ //Checks to make sure each element of the arraylists are equal 
        if(arrLst1.size() != arrLst2.size()){
            return false;
        }
        for(int i = 0; i < arrLst1.size(); i++){
            if(!arrLst1.get(i).equals(arrLst2.get(i))){
                return false;
            }
        }
        return true;
    }

    
}
