/*David Wang CSE 175 Fall 2019 */

//
// BackwardChain
//
// This class implements a backward chaining inference procedure. The
// implementation is very skeletal, and the resulting reasoning process is
// not particularly efficient. Knowledge is restricted to the form of
// definite clauses, grouped into a list of positive literals (facts) and
// a list of Horn clause implications (rules). The inference procedure
// maintains a list of goals. On each step, a proof is sought for the
// first goal in this list, starting by an attempt to unify the goal with
// any known fact in the knowledge base. If this fails, the rules are
// examined in the order in which they appear in the knowledge base, searching
// for a consequent that unifies with the goal. Upon successful unification,
// a proof is sought for the conjunction of the rule antecedents. If this
// fails, further rules are considered. Note that this is a strictly
// depth-first approach, so it is incomplete. Note, also, that there is
// no backtracking with regard to matches to facts -- the first match is
// always taken and other potential matches are ignored. This can make
// the algorithm incomplete in another way. In short, the order in which
// facts and rules appear in the knowledge base can have a large influence
// on the behavior of this inference procedure.
//
// In order to use this inference engine, the knowledge base must be
// initialized by a call to "initKB". Queries are then submitted using the
// "ask" method. The "ask" function returns a binding list which includes
// bindings for intermediate variables.
//
// David Noelle -- Tue Oct  9 18:48:57 PDT 2018
//


import java.util.*;


public class BackwardChain {

    public KnowledgeBase kb;

	// Default constructor ...
	public BackwardChain() {
		this.kb = new KnowledgeBase();
	}

	// initKB -- Initialize the knowledge base by interactively requesting
	// file names and reading those files. Return false on error.
	public boolean initKB() {
		return (kb.readKB());
	}

	// unify -- Return the most general unifier for the two provided literals,
	// or null if no unification is possible. The returned binding list
	// should be freshly allocated.
	public BindingList unify(Literal lit1, Literal lit2, BindingList bl) {

		// PROVIDE YOUR CODE HERE!

		Predicate a = lit1.pred;
		Predicate b = lit2.pred;

		ArrayList<Term> arg1 = new ArrayList<Term>();
		ArrayList<Term> arg2 = new ArrayList<Term>();

		arg1.addAll(lit1.args);
		arg2.addAll(lit2.args);

		//First, check if binding list is empty
		if (bl == null)
		{
			return null; //return null if binding list is empty
		}
		
		if(a.equals(b)) //check if lit1 and lit2's predicate member are equal
		{
			//if equal, call unify with respective args and bl
			return unify(arg1, arg2, bl);
		}

		return (null);
	}

	// unify -- Return the most general unifier for the two provided terms,
	// or null if no unification is possible. The returned binding list
	// should be freshly allocated.
	public BindingList unify(Term t1, Term t2, BindingList bl) 
	{

		// PROVIDE YOUR CODE HERE!
		
		Constant c1 = t1.c; //t1 constant
		Variable v1 = t1.v; //t1 variable
		Function f1 = t1.f; //t1 function

		Constant c2 = t2.c; //t2 constant
		Variable v2 = t2.v; //t2 variable
		Function f2 = t2.f; //t2 function

		//BindingList newList = new BindingList(bl);
		
		if(bl == null) //check if binding list is empty
		{
			return null; //return null if list is empty
		}

		//check if constants are not equal to null
		if(c1 != null) //if t1 constant is NOT null
		{
			if(c2 != null) //if t2 constant is NOT null
			{

				if(t1.equals(t2) == false) //check if t1 = t2
				{
					return null; //return null if t1 != t2
				}

				else //if t1 == t2
				{
					//if constants are not null and t1 = t2, then return original binding list
					return new BindingList(bl);
				}
				
			}
			
			else if (v2 != null) //check if variables are not null
			{
				//if v2 is not null and t1 is not null, bind and call unify
				return unify(t2, t1, bl);
			}
		}

		//check t1 variable
		else if(v1 != null)
		{
			Term index = bl.boundValue(v1); //store original value of v1 into temporary term for later reference

			if(index != null)
			{
				return unify(index, t2, bl);
			}

			else if(c2 != null) //If c2 != null, v1 is free
			{
				//bind t1 and t2 if c2 (t1.c) is not null
				Binding i = new Binding(v1, t2);
				bl.addBinding(i);
				return new BindingList(bl);
			}

			else if (v2 != null)
			{

				if(t1.equals(t2) == true)
				{
					//if equal, return original bindinglist
					return bl;
				}

				Binding i = new Binding(v1, t2);
				bl.addBinding(i);
				return new BindingList(bl);
			}

			else if(f2.allVariables().contains(v1) == false)
			{
				Binding i = new Binding(v1, t2);
				bl.addBinding(i);
				return new BindingList(bl);
			}
			else
			{
				if(f2.allVariables().contains(t1) == true)
				{
					return null;
				}
			}
		}

		else //if f1 != null
		{
			if(c2 != null)	//t1 function, t2 constant
			{
				return null;
			}
			else if(v2 != null) //t1 function, t2 variable
			{
				return unify(t2, t1, bl);
			}
			else //t1 function, t2 function
			{
				return unify(f1, f2, bl);
			}
		}

		return (null);
	}

	// unify -- Return the most general unifier for the two provided functions,
	// or null if no unification is possible. The returned binding list
	// should be freshly allocated.
	public BindingList unify(Function f1, Function f2, BindingList bl) 
	{

		// PROVIDE YOUR CODE HERE!

		FunctionName a = f1.func;
		FunctionName b = f2.func;

		ArrayList<Term> arg1 = new ArrayList<Term>();
		ArrayList<Term> arg2 = new ArrayList<Term>();

		arg1.addAll(f1.args);
		arg2.addAll(f2.args);

		//First, check if binding list is empty
		if (bl == null)
		{
			return null; //return null if binding list is empty
		}
		
		if(a.equals(b)) //check if lit1 and lit2's predicate member are equal
		{
			//if equal, call unify with respective args and bl
			return unify(arg1, arg2, bl);
		}

		return (null);
	}

	// unify -- Return the most general unifier for the two provided lists of
	// terms, or null if no unification is possible. The returned binding
	// list should be freshly allocated.
	public BindingList unify(List<Term> ts1, List<Term> ts2, BindingList bl) {
		if (bl == null)
			return (null);
		if ((ts1.size() == 0) && (ts2.size() == 0))
			// Empty lists match other empty lists ...
			return (new BindingList(bl));
		if ((ts1.size() == 0) || (ts2.size() == 0))
			// Ran out of arguments in one list before reaching the
			// end of the other list, which means the two argument lists
			// can't match ...
			return (null);
		List<Term> terms1 = new LinkedList<Term>();
		List<Term> terms2 = new LinkedList<Term>();
		terms1.addAll(ts1);
		terms2.addAll(ts2);
		Term t1 = terms1.get(0);
		Term t2 = terms2.get(0);
		terms1.remove(0);
		terms2.remove(0);
		return (unify(terms1, terms2, unify(t1, t2, bl)));
	}

	// askFacts -- Examine all of the facts in the knowledge base to
	// determine if any of them unify with the given literal, under the
	// given binding list. If a unification is found, return the
	// corresponding most general unifier. If none is found, return null
	// to indicate failure.
	BindingList askFacts(Literal lit, BindingList bl) {
		BindingList mgu = null; // Most General Unifier
		for (Literal fact : kb.facts) {
			mgu = unify(lit, fact, bl);
			if (mgu != null)
				return (mgu);
		}
		return (null);
	}

	// askFacts -- Examine all of the facts in the knowledge base to
	// determine if any of them unify with the given literal. If a
	// unification is found, return the corresponding most general unifier.
	// If none is found, return null to indicate failure.
	BindingList askFacts(Literal lit) {
		return (askFacts(lit, new BindingList()));
	}

	// ask -- Try to prove the given goal literal, under the constraints of
	// the given binding list, using both the list of known facts and the
	// collection of known rules. Terminate as soon as a proof is found,
	// returning the resulting binding list for that proof. Return null if
	// no proof can be found. The returned binding list should be freshly
	// allocated.
	BindingList ask(Literal goal, BindingList bl) {
		BindingList result = askFacts(goal, bl);
		if (result != null) {
			// The literal can be unified with a known fact ...
			return (result);
		}
		// Need to look at rules ...
		for (Rule candidateRule : kb.rules) {
			if (candidateRule.consequent.pred.equals(goal.pred)) {
				// The rule head uses the same predicate as the goal ...
				// Standardize apart ...
				Rule r = candidateRule.standardizeApart();
				// Check to see if the consequent unifies with the goal ...
				result = unify(goal, r.consequent, bl);
				if (result != null) {
					// This rule might be part of a proof, if we can prove
					// the rule's antecedents ...
					result = ask(r.antecedents, result);
					if (result != null) {
						// The antecedents have been proven, so the goal
						// is proven ...
						return (result);
					}
				}
			}
		}
		// No rule that matches has antecedents that can be proven. Thus,
		// the search fails ...
		return (null);
	}

	// ask -- Try to prove the given goal literal using both the list of
	// known facts and the collection of known rules. Terminate as soon as
	// a proof is found, returning the resulting binding list for that proof.
	// Return null if no proof can be found. The returned binding list
	// should be freshly allocated.
	BindingList ask(Literal goal) {
		return (ask(goal, new BindingList()));
	}

	// ask -- Try to prove the given list of goal literals, under the
	// constraints of the given binding list, using both the list of known
	// facts and the collection of known rules. Terminate as soon as a proof
	// is found, returning the resulting binding list for that proof. Return
	// null if no proof can be found. The returned binding list should be
	// freshly allocated.
	BindingList ask(List<Literal> goals, BindingList bl) {
		if (goals.size() == 0) {
			// All goals have been satisfied ...
			return (bl);
		} else {
			List<Literal> newGoals = new LinkedList<Literal>();
			newGoals.addAll(goals);
			Literal goal = newGoals.get(0);
			newGoals.remove(0);
			BindingList firstBL = ask(goal, bl);
			if (firstBL == null) {
				// Failure to prove one of the goals ...
				return (null);
			} else {
				// Try to prove the remaining goals ...
				return (ask(newGoals, firstBL));
			}
		}
	}

}
