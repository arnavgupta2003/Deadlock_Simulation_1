<H1 align = "center"> Deadlocks In Linux </H1>
<p align="Left">
  -> Implementing functions to simulate the custom Dining Philosophers Problem. 
  <br> -> Launching five threads, each of which relies on three different
functions, Thr_A(),Thr_B(),Thr_C(),Thr_D() and Thr_E().
  <br>
  -> Launching Varied versions of the problem and their solutions:
   <ul>
    <li>launchThreads_1(Simulate the Problem)</li>
    <li>launchThreads_2(Avoid deadlock using Serialization)</li>
    <li>launchThreads_3(Avoid deadlock using Semaphores)</li>
    <li>launchThreads_4(Two sauce Bowls.. Avoid deadlock using Semaphores)</li>
    </ul>

</p>

### Note
  The STDOUT in the Question is facing Race Conditions, hence the output observed may/may not be in the order in which the processes are running.

## Q1) Modified Dining Philosophers Problem
<p align="Left">
The dining philosophers problem contains five philosophers sitting on a round
table can perform only one among two actions – eat and think. For eating, each
of them requires two forks, one kept beside each person. Typically, allowing
unrestricted access to the forks may result in a deadlock.  
  <br> 
</p>

## `Installation`

```console
# Navigate to src/1
$> cd src/1

# run the makefile
$> make -f Makefile
       OR
$> make

# clean
$> make clean

```
## `Technologies Used`
<ul>
<li>Semaphores</li>
<li>Multi-Threading</li>
<li>Mutex Locks</li>
</ul>


## License

MIT © Arnav Gupta 2022<br/>
Original Creator - [Arnav Gupta](https://github.com/arnavgupta2003)
<br><br>
MIT License

Copyright (c) 2022 Arnav Gupta

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
<br>

<p align=center> --- EOF --- </p>
