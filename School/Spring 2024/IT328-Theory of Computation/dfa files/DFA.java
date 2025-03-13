import java.util.ArrayList;

public class DFA {
    int numStates;
    char[] sigma;
    int initialState;
    State[] states;

    public DFA(){

    }

    public DFA(ArrayList<ArrayList<Integer>> statesToAdd, ArrayList<ArrayList<Integer>> transition, char[] sigma, ArrayList<Boolean> isAccepting){
        numStates = statesToAdd.size();
        this.sigma = sigma;
        initialState = 0;
        states = new State[statesToAdd.size()];
        for(int i = 0; i < statesToAdd.size(); i++){
            states[i] = new State(transition.get(i), isAccepting.get(i));
        }
    }

    public String toString(){
        String str = "|Q|: " + numStates + "\nSigma:";
        String dash = "------";
        String accepting = "Accepting State(s): ";
        boolean firstAccept = true;
        for(int i = 0; i < sigma.length; i++){
            str += "     " + sigma[i];
            dash += "------";
        }
        str += '\n' + dash + '\n';
        for(int i = 0; i < states.length; i++){
            if(i < 10){
                str += "    " + i + ":" + states[i].toString() + "\n";
            }
            else if(i < 100){
                str += "   " + i + ":" + states[i].toString() + "\n";
            }
            else if(i < 1000){
                str += "  " + i + ":" + states[i].toString() + "\n";
            }
            else{
                str += " " + i + ":" + states[i].toString() + "\n";
            }
            
            if(states[i].isAccepting){
                if(!firstAccept){
                    accepting += "," + i;
                }
                else{
                    accepting += i;
                    firstAccept = false;
                }
            }
        }
        str += dash + '\n';
        str += "Initial State: " + initialState + '\n';
        str += accepting;
        return str;
    }

    public boolean toState(String omega){
        return scanChar(omega, 0, initialState);
    }

    private boolean scanChar(String omega, int charPos, int curState){
        if(charPos == omega.length()){
            return this.states[curState].isAccepting;
        }
        else{
            char curChar = omega.charAt(charPos);
            int sigmaPos = -1;
            for(int i = 0; i < sigma.length; i++){
                if(sigma[i] == curChar){
                    sigmaPos = i;
                }
            }
            charPos++;
            if(curChar == -1){
                return false;
            }
            else{
                return scanChar(omega, charPos, states[curState].transition[sigmaPos]);
            }
            
        }
    }

    public ArrayList<Boolean> getAccepting(){
        ArrayList<Boolean> acceptingStates = new ArrayList<>();

        for(State s : states){
            acceptingStates.add(s.isAccepting);
        }
        return acceptingStates;
    }

    public int[][] getTrans(){
        int[][] transition = new int[numStates][sigma.length];

        for(int i = 0; i < states.length; i++){
            int[] temp = states[i].transition;
            for(int j = 0; j < sigma.length; j++){
                transition[i][j] = temp[j];
            }
        }

        return transition;
    }


    class State{
        boolean isAccepting;
        int[] transition;

        public State(ArrayList<Integer> transLoc, boolean accept){
            isAccepting = accept;
            transition = new int[transLoc.size()];
            for(int i = 0; i < transition.length; i++){
                transition[i] = transLoc.get(i);
            }
        }

        public String toString(){
            String str = "";
            for(int i = 0; i<transition.length; i++){
                if(transition[i] < 10){
                    str += "     " + transition[i];
                }
                else if(transition[i] < 100){
                    str += "    " + transition[i];
                }
                else if(transition[i] < 1000){
                    str += "   " + transition[i];
                }
                else{
                    str += "  " + transition[i];
                }
                
            }
            return str;
        }
    }

}
