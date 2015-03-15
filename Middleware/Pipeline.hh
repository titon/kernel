<?hh // strict
/**
 * @copyright   2010-2015, The Titon Project
 * @license     http://opensource.org/licenses/bsd-license.php
 * @link        http://titon.io
 */

namespace Titon\Kernel\Middleware;

use Titon\Kernel\Input;
use Titon\Kernel\Middleware;
use Titon\Kernel\Output;
use SplQueue;

/**
 * The Pipeline handles the management of middleware through the use of a queue data structure.
 *
 * @package Titon\Kernel\Middleware
 */
class Pipeline<Ti as Input, To as Output> {

    /**
     * Queued middleware items.
     *
     * @var \SplQueue
     */
    protected SplQueue<Middleware<Ti, To>> $pipeline;

    /**
     * Create a new queue to store middleware.
     */
    public function __construct() {
        $this->pipeline = new SplQueue();
    }

    /**
     * Start the pipeline process by executing the first middleware in the queue,
     * and passing a handler for the next middleware as an argument callback.
     *
     * @param \Titon\Kernel\Input $input
     * @param \Titon\Kernel\Output $output
     * @return \Titon\Kernel\Output
     */
    public function handle(Ti $input, To $output): To {
        return (new Next($this->pipeline))->handle($input, $output);
    }

    /**
     * Add a middleware to the queue.
     *
     * @param \Titon\Kernel\Middleware $middleware
     * @return $this
     */
    public function through(Middleware<Ti, To> $middleware): this {
        $this->pipeline->enqueue($middleware);

        return $this;
    }

}
